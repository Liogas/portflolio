#include "EventSDL.hpp"

EventSDL::EventSDL()
{
	std::cout << "EventSDL created" << std::endl;
}

EventSDL::~EventSDL()
{
	std::cout << "EventSDL destroyed" << std::endl;
}

bool	EventSDL::poll(SDL_Event *e)
{
	return (SDL_PollEvent(e));
}
