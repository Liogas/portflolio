#include "TextureSDL.hpp"

TextureSDL::TextureSDL(RendererSDL &renderer, const std::string &path):
	_renderer(renderer)
{
	this->_texture = this->_renderer.loadImg((char *)path.c_str());
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
	if (SDL_RenderCopy(
		this->_renderer.getRenderer(),
		this->_texture,
		src,
		dst
	) < 0)
		return (false);
	return (true);
}