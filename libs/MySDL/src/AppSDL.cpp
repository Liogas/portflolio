#include "AppSDL.hpp"

AppSDL::AppSDL(ESDLOption option)
{
	if (SDL_Init(static_cast<Uint32>(option)))
		throw std::runtime_error(SDL_GetError());
	int flags = IMG_INIT_PNG | IMG_INIT_JPG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags)
    	throw std::runtime_error(IMG_GetError());
	if (TTF_Init())
		throw std::runtime_error(TTF_GetError());
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	std::cout << "SDL initialized" << std::endl;
}

AppSDL::~AppSDL()
{
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	std::cout << "SDL quited" << std::endl;
}