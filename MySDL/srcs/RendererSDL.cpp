#include "RendererSDL.hpp"

RendererSDL::RendererSDL(WindowSDL &win, ERendererOption opt)
{
	this->_renderer = SDL_CreateRenderer(
		win.getWindow(),
		-1,
		static_cast<Uint32>(opt)
	);
	if (!this->_renderer)
		throw std::runtime_error(SDL_GetError());
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

SDL_Texture	*RendererSDL::loadImg(const char *path)
{
	SDL_Texture	*texture = NULL;

	SDL_Texture	*tmp = IMG_LoadTexture(this->_renderer, path);
	if (!tmp)
		throw std::runtime_error(IMG_GetError());
	int	w, h;
	if (SDL_QueryTexture(tmp, NULL, NULL, &w, &h) != 0)
	{
		SDL_DestroyTexture(tmp);
		throw std::runtime_error(SDL_GetError());
	}
	texture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888,
				SDL_TEXTUREACCESS_TARGET, w, h);
	if (!texture)
	{
		SDL_DestroyTexture(tmp);
		throw std::runtime_error(SDL_GetError());
	}
	SDL_SetRenderTarget(this->_renderer, texture);
	if (SDL_RenderCopy(this->_renderer, tmp, NULL, NULL) != 0)
	{
		SDL_DestroyTexture(tmp);
		SDL_DestroyTexture(texture);
		SDL_RenderTarget(this->_renderer, NULL);
		throw std::runtime_error(SDL_GetError());
	}
	SDL_SetRenderTarget(this->_renderer, NULL);
	SDL_DestroyTexture(tmp);
	return (texture);
}
