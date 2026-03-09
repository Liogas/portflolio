#include "TextureSDL.hpp"

TextureSDL::TextureSDL(RendererSDL &renderer, const std::string &path):
	_renderer(renderer)
{
	this->_texture = this->_renderer.loadImg(path.c_str());
	if (!this->_texture)
		throw std::runtime_error("Error texture sdl");
	std::cout << "TextureSDL created" << std::endl;
}

TextureSDL::~TextureSDL()
{
	SDL_DestroyTexture(this->_texture);
	std::cout << "TextureSDL destroyed" << std::endl;
}

SDL_Texture	*TextureSDL::getTexture() const
{
	return (this->_texture);
}

bool	TextureSDL::render(SDL_Rect *src, SDL_Rect *dst)
{
	return (SDL_RenderCopy(
		this->_renderer.getRenderer(),
		this->_texture,
		src,
		dst
	) == 0;
}

void	TextureSDL::getSize(int *w, int *h)
{
	SDL_QueryTexture(this->_texture, NULL, NULL, w, h);
}

void	TextureSDL::setAsTarget()
{
	if (SDL_SetRenderTarget(this->_renderer, this->_texture) == -1)
		throw std::runtime_error(SDL_GetError());
}

void	TextureSDL::resetTarget()
{
	if (SDL_SetRenderTarget(this->_renderer, NULL) == -1)
		throw std::runtime_error(SDL_GetError());
}
