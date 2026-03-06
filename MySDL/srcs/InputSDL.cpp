#include "InputSDL.hpp"

InputSDL::InputSDL():
	_keyboard(nullptr)
{
	std::cout << "InputSDL created" << std::endl;
}

InputSDL::~InputSDL()
{
	std::cout << "InputSDL deleted" << std::endl;
}

void	InputSDL::update()
{
	SDL_PumpEvents();
	this->_keyboard = SDL_GetKeyboardState(NULL);
}

bool	InputSDL::isKeyPressed(SDL_Scancode code)
{
	if (this->_keyboard[code])
		return (true);
	return (false);
}