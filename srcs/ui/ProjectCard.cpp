#include "ProjectCard.hpp"

namespace
{
	inline float lerpf(float a, float b, float t)
	{ 
		return (a + (b - a) * t);
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
			UIStyle::applyPercentage(UIStyle::Caroussel::CardWidth, container.w),
			UIStyle::applyPercentage(UIStyle::Caroussel::CardHeight, container.h)
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
		this->buildTitle(renderer, rm, w);
		this->buildDescription(renderer, rm, w, h);
		this->buildImage(rm, w, h);
		this->buildTags(rm, w, h);
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
	int					containerW
)
{
	UIText title;
	title.setText(
		this->project->title,
		r,
		rm.getFont(
			UIStyle::Card::Title::Font,
			UIStyle::Card::Title::Size
		),
		UIStyle::Card::Title::Color
	);
	title.rect.y = UIStyle::applyPercentage(UIStyle::Card::Spacing, containerW);
	title.rect.x = (containerW - title.rect.w) / 2;
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
			UIStyle::Card::Desc::Font,
			UIStyle::Card::Desc::Size
		),
		UIStyle::Card::Desc::Color
	);
	desc.rect.y = UIStyle::applyPercentage(UIStyle::Card::Title::Height, containerH) + UIStyle::Card::Spacing;
	desc.rect.x = UIStyle::applyPercentage(UIStyle::Card::Spacing, desc.rect.w);
	desc.rect.w = containerW - UIStyle::Card::Spacing * 3;
	desc.draw(r);
}

void	ProjectCard::buildImage(
	RessourceManager	&rm,
	int					containerW,
	int					containerH
)
{
	std::shared_ptr<TextureSDL> &img = rm.getTexture("imageEmpty.png");
	int	w, h;
	int y = 
		UIStyle::applyPercentage(UIStyle::Card::Title::Height, containerH)
		+ UIStyle::applyPercentage(UIStyle::Card::Spacing, containerH)
		+ UIStyle::applyPercentage(UIStyle::Card::Desc::Height, containerH);
	img->getSize(&w, &h);
	SDL_Rect rect = {
		UIStyle::applyPercentage(UIStyle::Card::Spacing, containerW),
		y,
		containerW - UIStyle::applyPercentage(UIStyle::Card::Spacing, containerW) * 2,
		UIStyle::applyPercentage(UIStyle::Card::Img::Height, containerH)
	};
	img->render(nullptr, &rect);
}

void	ProjectCard::buildTags(
	RessourceManager	&rm,
	int					containerW,
	int					containerH
)
{
	const std::vector<std::string> &tags = this->project->tags;
	int	x = UIStyle::applyPercentage(UIStyle::Card::Spacing, containerW);
	int y = UIStyle::applyPercentage(UIStyle::Card::Title::Height, containerH)
		+ UIStyle::applyPercentage(UIStyle::Card::Spacing, containerH) * 2
		+ UIStyle::applyPercentage(UIStyle::Card::Desc::Height, containerH)
		+ UIStyle::applyPercentage(UIStyle::Card::Img::Height, containerH);
	int size = UIStyle::applyPercentage(UIStyle::Card::Tags::Height, containerH);
	std::cout << "size -> " << size << std::endl;
	for (size_t i = 0; i < tags.size(); i++)
	{
		std::string path = tags[i] + ".png";
		std::shared_ptr<TextureSDL> &img = rm.getTexture(path);
		SDL_Rect rect = {
			x,
			y,
			size,
			size
		};
		img->render(nullptr, &rect);
	}
}

void    ProjectCard::buildCoverflowMesh(
    int                         centerX,
    int							centerY,
    std::vector<SDL_Vertex>    	&vertices,
    std::vector<int>           	&indices
) const
{
    constexpr int slices = UIStyle::Caroussel::CoverflowSlices;

    float width = this->rect.w * lerpf(1.0f, UIStyle::Caroussel::SideWidthRatio, this->depthT);
    float nearH = this->rect.h * lerpf(1.0f, UIStyle::Caroussel::SideNearHeightRatio, this->depthT);
    float farH  = nearH * lerpf(1.0f, UIStyle::Caroussel::SideFarHeightRatio, this->depthT);
    float left  = centerX - width / 2.f;

    Uint8 brightness = (Uint8)(255 * lerpf(1.0f, UIStyle::Caroussel::SideBrightness, this->depthT));
    SDL_Color tint = { brightness, brightness, brightness, 255 };

    vertices.clear();
    indices.clear();
    vertices.reserve((slices + 1) * 2);
    indices.reserve(slices * 6);

    for (int i = 0; i <= slices; ++i)
    {
        float u = (float)i / (float)slices;
        float h = (this->side > 0) ? lerpf(nearH, farH, u) : lerpf(farH, nearH, u);
        float x = left + u * width;

        vertices.push_back({ { x, centerY - h / 2.f }, tint, { u, 0.f } });
        vertices.push_back({ { x, centerY + h / 2.f }, tint, { u, 1.f } });
    }
    for (int i = 0; i < slices; ++i)
    {
        int top0 = i * 2, bot0 = i * 2 + 1;
        int top1 = (i + 1) * 2, bot1 = (i + 1) * 2 + 1;
        indices.push_back(top0); indices.push_back(top1); indices.push_back(bot0);
        indices.push_back(bot0); indices.push_back(top1); indices.push_back(bot1);
    }
}

void    ProjectCard::draw(RendererSDL &renderer)
{
    int centerX = this->rect.x + this->rect.w / 2;
    int centerY = this->rect.y + this->rect.h / 2;

    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;
    this->buildCoverflowMesh(centerX, centerY, vertices, indices);

    if (SDL_RenderGeometry(renderer.getRenderer(), this->texture, vertices.data(), (int)vertices.size(), indices.data(), (int)indices.size()) < 0)
        std::cerr << "SDL_RenderGeometry: " << SDL_GetError() << std::endl;
}

void	ProjectCard::open()
{
	std::string url = this->project->githubUrl;
	#if defined(_WIN32)
		ShellExecuteA(
			nullptr,
			"open",
			url.c_str(),
			nullptr,
			nullptr,
			SW_SHOWNORMAL
		);
	#elif defined(__APPLE__) || defined(__linux__)
		pid_t pid = fork();
		if (pid == 0)
		{
			#if defined(__APPLE__)
				execlp("open", "open", url.c_str(), nullptr);
			#else
				execlp("xdg-open", "xdg-open", url.c_str(), nullptr);
			#endif
			_exit(1);
		}
	#else
		throw (std::runtime_error("Error ProjectCard::open -> Unsupported platform"));
	#endif
}
