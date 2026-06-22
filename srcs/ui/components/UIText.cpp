#include "UIText.hpp"

UIText::UIText()
{
	this->_texture = nullptr;
	this->_wrapWidth = 0;
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

void UIText::setText(
    const std::string   &text,
    RendererSDL         &renderer,
    TTF_Font            *font,
    SDL_Color           color
)
{
    if (this->_texture)
        SDL_DestroyTexture(this->_texture);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_Surface *surface;
    if (this->_wrapWidth > 0)
    	surface = TTF_RenderUTF8_LCD_Wrapped(font, text.c_str(), color, {70,70,70,255}, this->_wrapWidth);
	else
    	surface = TTF_RenderUTF8_LCD(font, text.c_str(), color, {70,70,70,255});
    if (!surface)
        throw std::runtime_error(TTF_GetError());
    this->_texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface);
    SDL_FreeSurface(surface);
    if (!this->_texture)
        throw std::runtime_error(SDL_GetError());
    SDL_SetTextureBlendMode(this->_texture, SDL_BLENDMODE_BLEND);
    SDL_QueryTexture(this->_texture, nullptr, nullptr, &this->rect.w, &this->rect.h);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
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