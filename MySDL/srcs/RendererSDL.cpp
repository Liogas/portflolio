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