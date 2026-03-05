#include "RendererSDL.hpp"

RendererSDL::RendererSDL(WindowSDL &win, ERendererOption opt)
{
	this->_renderer = SDL_CreateRenderer(
		win.getWindow(),
		-1,
		static_cast<Uint32>(opt)
	);
}

RendererSDL::~RendererSDL()
{
	SDL_DestroyRenderer(this->_renderer);
	std::cout << "Renderer destroyed" << std::endl;
}

void	RendererSDL::present()
{
	SDL_RenderPresent(this->_renderer);
}

void	RendererSDL::clear()
{
	if (SDL_RenderClear(this->_renderer) < 0)
		throw std::runtime_error(SDL_GetError());
}

void	RendererSDL::setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	if (SDL_SetRenderDrawColor(this->_renderer, r, g, b, a) < 0)
		throw std::runtime_error(SDL_GetError());
}

SDL_Renderer	*RendererSDL::getRenderer() const
{
	return (this->_renderer);
}

SDL_Texture	*RendererSDL::loadImg(char *path)
{
	SDL_Surface	*surface = NULL;
	SDL_Texture	*texture, *tmp = NULL;

	surface = SDL_LoadBMP(path);
	if (!surface)
	{
		std::cerr << "Error on load : " << SDL_GetError() << std::endl;
		return (NULL);
	}
	tmp = SDL_CreateTextureFromSurface(this->_renderer, surface);
	if (!tmp)
	{
		std::cerr << "Error on create texture from surface : " << SDL_GetError() << std::endl;
		return (NULL);
	}
	texture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888,
				SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
	if (!texture)
	{
		std::cerr << "Error on create texture : " << SDL_GetError() << std::endl;
		return (NULL);
	}
	SDL_SetRenderTarget(this->_renderer, texture);
	SDL_RenderCopy(this->_renderer, tmp, NULL, NULL);
	SDL_DestroyTexture(tmp);
	SDL_FreeSurface(surface);
	SDL_SetRenderTarget(this->_renderer, NULL);
	return (texture);
}
