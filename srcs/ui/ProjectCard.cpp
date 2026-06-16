#include "ProjectCard.hpp"

namespace
{
	inline float lerpf(float a, float b, float t)
	{
		return (a +(b - a) * t);
	}
}

ProjectCard::ProjectCard(
	const Project 		*p,
	RendererSDL			&renderer,
	RessourceManager	&rm,
	SDL_Rect			&container
)
{
	this->project = p;
	this->texture = nullptr;
	this->dirty = true;
	this->depthT = 0.f;
	this->side = 0;
	this->update(renderer, rm, container);
}

ProjectCard::~ProjectCard()
{
	if (this->texture)
		SDL_DestroyTexture(this->texture);
}

ProjectCard::ProjectCard(ProjectCard&& other) noexcept
{
    this->project = other.project;
    this->texture = other.texture;
    this->rect = other.rect;
    this->dirty = other.dirty;
	this->depthT = other.depthT;
	this->side = other.side;
    other.texture = nullptr;
}

ProjectCard& ProjectCard::operator=(ProjectCard&& other) noexcept
{
    if (this != &other)
    {
        if (this->texture)
            SDL_DestroyTexture(this->texture);

        this->project = other.project;
        this->texture = other.texture;
        this->rect = other.rect;
        this->dirty = other.dirty;
		this->depthT = other.depthT;
		this->side = other.side;
        other.texture = nullptr;
    }
    return (*this);
}

void	ProjectCard::update(
	RendererSDL 		&renderer,
	RessourceManager 	&rm,
	SDL_Rect			&container
)
{
	if (!this->dirty)
		return ;
	this->rebuild(renderer, rm, container);
	this->dirty = false;
}

void	ProjectCard::rebuild(
	RendererSDL 		&renderer,
	RessourceManager	&rm,
	SDL_Rect			&container
)
{
	try
	{
		auto *r = renderer.getRenderer();
		if (this->texture)
			SDL_DestroyTexture(this->texture);
		this->texture = SDL_CreateTexture(
			r,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			UIStyle::applyPercentage(UIStyle::Caroussel::MainWidth, container.w),
			UIStyle::applyPercentage(UIStyle::Caroussel::MainHeight, container.h)
		);
		if (!this->texture)
			throw (std::runtime_error(SDL_GetError()));
		SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(renderer.getRenderer(), this->texture);
		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
		SDL_RenderClear(r);
		int	w, h;
		SDL_QueryTexture(this->texture, nullptr, nullptr, &w, &h);
		this->rect = {
			container.x + container.w / 2 - w / 2,
			container.y + container.h / 2 - h / 2,
			w,
			h 
		};
		this->buildContainer(renderer);
		this->buildTitle(renderer, rm, w, h);
		// this->buildTags(r);
		this->buildDescription(renderer, rm, w, h);

		SDL_SetRenderTarget(r, nullptr);
	} catch (const std::exception &e)
	{
		std::cerr << "ERRREUR BIEN DETECTE ICI" << std::endl;
		throw (std::runtime_error(SDL_GetError()));
	}
	
}

void	ProjectCard::buildContainer(RendererSDL &renderer)
{
	SDL_Renderer *r = renderer.getRenderer();
	SDL_Rect tmp {
		0,
		0,
		this->rect.w,
		this->rect.h
	};
	UIStyle::applyColor(r, UIStyle::Card::BkgColor);
	SDL_RenderFillRect(r, &tmp);
	UIStyle::applyColor(r, UIStyle::Card::BorderColor);
	SDL_RenderDrawRect(r, &tmp);
}

void	ProjectCard::buildTitle(
	RendererSDL 		&r,
	RessourceManager	&rm,
	int					containerW,
	int					containerH
)
{
	UIText title;
	title.setText(
		this->project->title,
		r,
		rm.getFont(
			std::string(UIStyle::Font::KGSketch18.path),
			UIStyle::Font::KGSketch18.size
		),
		UIStyle::Card::TitleColor
	);
	title.rect.x = (containerW - title.rect.w) / 2;
	title.rect.h = UIStyle::applyPercentage(UIStyle::Card::TitleHeight, containerH);
	title.draw(r);
}

void	ProjectCard::buildDescription(
	RendererSDL 		&r,
	RessourceManager	&rm,
	int					containerW,
	int					containerH
)
{
	UIText desc;
	desc.setWrapWidth(containerW);
	desc.setText(
		this->project->description,
		r,
		rm.getFont(
			std::string(UIStyle::Font::KGSolid8.path),
			UIStyle::Font::KGSolid8.size
		),
		UIStyle::Card::TitleColor
	);
	if (desc.rect.h > UIStyle::applyPercentage(UIStyle::Card::DescHeight, containerH))
		desc.rect.h = UIStyle::applyPercentage(UIStyle::Card::DescHeight, containerH);
	desc.rect.y = UIStyle::applyPercentage(UIStyle::Card::TitleHeight, containerH) + UIStyle::Card::Spacing;
	desc.rect.x = UIStyle::applyPercentage(UIStyle::Card::Spacing, desc.rect.w);
	desc.draw(r);
}

void	ProjectCard::draw(RendererSDL &renderer)
{
	int centerX = this->rect.x + this->rect.w / 2;
    int centerY = this->rect.y + this->rect.h / 2;

    CardQuad quad = this->computeQuad(centerX, centerY, this->rect.w, this->rect.h);

    Uint8 brightness = (Uint8)(255 * lerpf(1.0f, UIStyle::Caroussel::SideBrightness, this->depthT));
    SDL_Color tint = { brightness, brightness, brightness, 255 };

    SDL_Vertex vertices[4] = {
        { quad.tl, tint, { 0.f, 0.f } },
        { quad.tr, tint, { 1.f, 0.f } },
        { quad.bl, tint, { 0.f, 1.f } },
        { quad.br, tint, { 1.f, 1.f } },
    };
    int indices[6] = { 0, 1, 2, 2, 1, 3 };

    if (SDL_RenderGeometry(renderer.getRenderer(), this->texture, vertices, 4, indices, 6) < 0)
        std::cerr << "SDL_RenderGeometry: " << SDL_GetError() << std::endl;
}

CardQuad    ProjectCard::computeQuad(int centerX, int centerY, int mainW, int mainH) const
{
    float width = mainW * lerpf(1.0f, UIStyle::Caroussel::SideWidthRatio, this->depthT);
    float nearH = mainH * lerpf(1.0f, UIStyle::Caroussel::SideNearHeightRatio, this->depthT);
    float farH  = nearH * lerpf(1.0f, UIStyle::Caroussel::SideFarHeightRatio, this->depthT);

    float left  = centerX - width / 2.f;
    float right = centerX + width / 2.f;

    CardQuad q;
    if (this->side <= 0) // centre ou gauche : bord lointain à gauche
    {
        q.tl = { left,  centerY - farH  / 2.f };
        q.bl = { left,  centerY + farH  / 2.f };
        q.tr = { right, centerY - nearH / 2.f };
        q.br = { right, centerY + nearH / 2.f };
    }
    else // droite : bord lointain à droite
    {
        q.tl = { left,  centerY - nearH / 2.f };
        q.bl = { left,  centerY + nearH / 2.f };
        q.tr = { right, centerY - farH  / 2.f };
        q.br = { right, centerY + farH  / 2.f };
    }
    return (q);
}
