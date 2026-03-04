#include "AppSDL.hpp"

AppSDL::AppSDL(ESDLOption option)
{
	if (SDL_Init(static_cast<Uint32>(option)))
		throw std::runtime_error(SDL_GetError());
	std::cout << "SDL initialized" << std::endl;
}

AppSDL::~AppSDL()
{
	SDL_Quit();
	std::cout << "SDL quited" << std::endl;
}