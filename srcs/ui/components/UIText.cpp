#include "UIText.hpp"

UIText::UIText()
{
	this->_texture = nullptr;
	this->_wrapWidth = 0;
	std::cout << "UIText created" << std::endl;
}

UIText::~UIText()
{
	if (this->_texture)
		SDL_DestroyTexture(this->_texture);
}

UIText::UIText(UIText&& other) noexcept : 
	UIElement(std::move(other)),
	_texture(other._texture),
    _wrapWidth(other._wrapWidth)
{
    other._texture = nullptr;
}

UIText& UIText::operator=(UIText&& other) noexcept
{
    if (this != &other)
    {
        SDL_DestroyTexture(_texture);

        this->_texture = other._texture;
        this->_wrapWidth = other._wrapWidth;
        this->rect = other.rect;

        other._texture = nullptr;
    }

    return *this;
}

void	UIText::setText(
	const std::string 	&text,
	RendererSDL			&renderer,
	TTF_Font			*font,
	SDL_Color			color
)
{
	if (this->_texture)
		SDL_DestroyTexture(this->_texture);
	SDL_Surface *surface;
	if (this->_wrapWidth > 0)
	{
		surface = TTF_RenderUTF8_Blended_Wrapped(
			font,
			text.c_str(),
			color,
			this->_wrapWidth
		);
	} else
	{
		surface = TTF_RenderUTF8_Blended(
			font,
			text.c_str(),
			color
		);
	}
	if (!surface)
		throw (std::runtime_error(TTF_GetError()));
	this->_texture = SDL_CreateTextureFromSurface(
		renderer.getRenderer(),
		surface
	);
	if (!this->_texture)
	{
    	std::cerr << "Texture creation failed: " << SDL_GetError() << std::endl;
	}
	if (!this->_texture)
    	throw std::runtime_error(SDL_GetError());
	SDL_SetTextureBlendMode(this->_texture, SDL_BLENDMODE_BLEND);
	this->rect.w = surface->w;
	this->rect.h = surface->h;
	SDL_FreeSurface(surface);
}

void	UIText::setWrapWidth(int width)
{
	this->_wrapWidth = width;
}

void	UIText::draw(RendererSDL &renderer)
{
	if (!this->_texture)
	{
		std::cout << "UIText : No texture" << std::endl;
		return ;
	}
	SDL_RenderCopy(
		renderer.getRenderer(),
		this->_texture,
		nullptr,
		&this->rect
	);
}