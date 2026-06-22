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
	this->project		= p;
	this->texture		= nullptr;
	this->dirty			= true;
	this->theta			= 0.f;
	this->originX		= 0.f;
	this->originY		= 0.f;
	this->ringRadius	= 0.f;
	this->focal 		= 1.f;
	this->scrollY		= 0;
	this->contentH		= 0;
	this->update(renderer, rm, container);
}

ProjectCard::~ProjectCard()
{
	if (this->texture)
		SDL_DestroyTexture(this->texture);
}

ProjectCard::ProjectCard(ProjectCard&& other) noexcept
{
    this->project		= other.project;
    this->texture		= other.texture;
    this->rect			= other.rect;
    this->dirty			= other.dirty;
	this->theta			= other.theta;
	this->originX		= other.originX;
	this->originY		= other.originY;
	this->ringRadius	= other.ringRadius;
	this->focal 		= other.focal;
	this->contentH		= other.contentH;
	this->scrollY		= other.scrollY;
    other.texture		= nullptr;
}

ProjectCard& ProjectCard::operator=(ProjectCard&& other) noexcept
{
    if (this != &other)
    {
        if (this->texture)
            SDL_DestroyTexture(this->texture);

        this->project		= other.project;
		this->texture		= other.texture;
		this->rect			= other.rect;
		this->dirty			= other.dirty;
		this->theta			= other.theta;
		this->originX		= other.originX;
		this->originY		= other.originY;
		this->ringRadius	= other.ringRadius;
		this->focal 		= other.focal;
		this->contentH		= other.contentH;
		this->scrollY		= other.scrollY;
		other.texture		= nullptr;
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

void	ProjectCard::scroll(int delta)
{
	int maxScroll = std::max(0, this->contentH - this->rect.h);
	this->scrollY = std::clamp(this->scrollY + delta, 0, maxScroll);
	this->dirty = true;
}

void	ProjectCard::rebuild(
	RendererSDL 		&renderer,
	RessourceManager	&rm,
	SDL_Rect			&container
)
{
	try
	{
		if (!this->dirty)
			return ;
		auto *r = renderer.getRenderer();
		if (this->texture)
			SDL_DestroyTexture(this->texture);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
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
		int cursorY = -(this->scrollY);
		this->buildTitle(renderer, rm, w, h, cursorY);
		this->buildDescription(renderer, rm, w, h, cursorY);
		this->buildImage(rm, w, h, cursorY);
		this->buildTags(rm, w, h, cursorY);
		// stocke la hauteur totale pour connaitre le max de scroll
		this->contentH = cursorY + this->scrollY;
		// scrollbar
		if (this->contentH > h)
		{
			constexpr int barW   = UIStyle::Card::ScrollBar::W;
			constexpr int insetX = UIStyle::Card::ScrollBar::InsetX;
			constexpr int insetY = UIStyle::Card::ScrollBar::InsetY;

			int trackH  = h - insetY * 2;
			int barH    = std::max(16, (int)((float)trackH * trackH / this->contentH));
			int barMaxY = insetY + trackH - barH;
			int scrollRange = this->contentH - h;
			int barY    = insetY + (scrollRange > 0
							? (int)((float)barMaxY * this->scrollY / scrollRange)
							: 0);

			SDL_Rect track = { w - barW - insetX, insetY, barW, trackH };
			SDL_SetRenderDrawColor(r, 50, 50, 50, 200);
			SDL_RenderFillRect(r, &track);

			SDL_Rect thumb = { w - barW - insetX, barY, barW, barH };
			SDL_SetRenderDrawColor(r, 200, 200, 200, 220);
			SDL_RenderFillRect(r, &thumb);
		}
		UIStyle::applyColor(r, UIStyle::Card::BorderColor);
		SDL_Rect tmp {
			0,
			0,
			this->rect.w,
			this->rect.h
		};
		SDL_RenderDrawRect(r, &tmp);
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
}

void ProjectCard::buildTitle(
	RendererSDL &r,
	RessourceManager &rm,
	int containerW,
	int containerH,
	int &cursorY
)
{
	UIText title;
	title.setText(
		this->project->title, r,
		rm.getFont(
			UIStyle::Card::Title::Font,
			UIStyle::Card::Title::Size
		),
		UIStyle::Card::Title::Color
	);
	int marginTop = UIStyle::applyPercentage(UIStyle::Card::Spacing, containerH);
	cursorY += marginTop;
	int scrollReserve = UIStyle::Card::ScrollBar::W + UIStyle::Card::ScrollBar::InsetX + 2;
	title.rect.x = (containerW - scrollReserve - title.rect.w) / 2;
	title.rect.y = cursorY;
	title.draw(r);
	cursorY += title.rect.h;
}

void ProjectCard::buildDescription(
	RendererSDL &r,
	RessourceManager &rm,
	int containerW,
	int containerH,
	int &cursorY
)
{
	int marginX = UIStyle::applyPercentage(UIStyle::Card::Spacing, containerW);
	int marginTop = UIStyle::applyPercentage(UIStyle::Card::Spacing, containerH);
	int scrollReserve = UIStyle::Card::ScrollBar::W + UIStyle::Card::ScrollBar::InsetX + 2;
	int wrapWidth = containerW - marginX * 2 - scrollReserve;
	UIText desc;
	desc.setWrapWidth(wrapWidth);
	desc.setText(
		this->project->description, r,
		rm.getFont(
			UIStyle::Card::Desc::Font,
			UIStyle::Card::Desc::Size
		),
		UIStyle::Card::Desc::Color
	);
	cursorY += marginTop;
	desc.rect.y = cursorY;
	desc.rect.x = marginX;
	desc.rect.w = wrapWidth;
	desc.draw(r);
	cursorY += desc.rect.h;
}

void ProjectCard::buildImage(
    RessourceManager &rm,
    int containerW,
    int containerH,
    int &cursorY
)
{
    std::shared_ptr<TextureSDL> &img = rm.getTexture("imageEmpty.png");
    int marginX      = UIStyle::applyPercentage(UIStyle::Card::Spacing, containerW);
    int marginTop    = UIStyle::applyPercentage(UIStyle::Card::Spacing, containerH);
    int scrollReserve = UIStyle::Card::ScrollBar::W + UIStyle::Card::ScrollBar::InsetX + 2;
    int imgW         = containerW - marginX * 2 - scrollReserve;
    int imgH         = imgW * 9 / 16;  // ratio 16:9, change en 3/2 ou 4/3 selon ta preference

    cursorY += marginTop;
    SDL_Rect rect = { marginX, cursorY, imgW, imgH };
    img->render(nullptr, &rect);
    cursorY += imgH;
}

void ProjectCard::buildTags(
	RessourceManager &rm,
	int containerW,
	int containerH,
	int &cursorY
)
{
	const std::vector<std::string> &tags = this->project->tags;
	int marginX = UIStyle::applyPercentage(UIStyle::Card::Spacing, containerW);
	int marginTop = UIStyle::applyPercentage(UIStyle::Card::Spacing, containerH);
	int size = UIStyle::applyPercentage(UIStyle::Card::Tags::Height, containerH);

	cursorY += marginTop;
	int x = marginX;
	for (size_t i = 0; i < tags.size(); i++)
	{
		std::string path = tags[i] + ".png";
		std::shared_ptr<TextureSDL> &img = rm.getTexture(path);
		SDL_Rect rect = { x, cursorY, size, size };
		img->render(nullptr, &rect);
		x += size + marginX; // décale chaque tag, sinon ils s'empilent
	}
	cursorY += size;
}

void    ProjectCard::buildCoverflowMesh(
    std::vector<SDL_Vertex>    &vertices,
    std::vector<int>           &indices
) const
{
    constexpr int slices = UIStyle::Caroussel::CoverflowSlices;

    float cosT = cosf(this->theta);
    float sinT = sinf(this->theta);

    float ringX = this->ringRadius * sinT;
    float ringZ = this->ringRadius * (1.f - cosT);

    float visualDepth = ringZ / (2.f * this->ringRadius); // 0 = devant, 1 = tout au fond
    float brightness = lerpf(1.f, UIStyle::Caroussel::MinBrightness, visualDepth);
    Uint8 b = (Uint8)(255 * brightness);
    SDL_Color tint = { b, b, b, 255 };

    float hw = this->rect.w / 2.f;
    float hh = this->rect.h / 2.f;

    vertices.clear();
    indices.clear();
    vertices.reserve((slices + 1) * 2);
    indices.reserve(slices * 6);

    for (int i = 0; i <= slices; ++i)
    {
        float u = (float)i / (float)slices;
        float localX = -hw + u * (2.f * hw);

        float worldX = ringX + localX * cosT;
        float worldZ = ringZ + localX * sinT;
        float scale  = this->focal / (this->focal + worldZ);

        float screenX    = this->originX + worldX * scale;
        float screenTopY = this->originY - hh * scale;
        float screenBotY = this->originY + hh * scale;

        vertices.push_back({ { screenX, screenTopY }, tint, { u, 0.f } });
        vertices.push_back({ { screenX, screenBotY }, tint, { u, 1.f } });
    }
    for (int i = 0; i < slices; ++i)
    {
        int top0 = i * 2, bot0 = i * 2 + 1, top1 = (i + 1) * 2, bot1 = (i + 1) * 2 + 1;
        indices.push_back(top0); indices.push_back(top1); indices.push_back(bot0);
        indices.push_back(bot0); indices.push_back(top1); indices.push_back(bot1);
    }
}

void    ProjectCard::draw(RendererSDL &renderer)
{
    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;
    this->buildCoverflowMesh(vertices, indices);
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
