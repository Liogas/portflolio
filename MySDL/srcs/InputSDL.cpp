#include "InputSDL.hpp"

InputSDL::InputSDL():
	_keyboard(nullptr)
{
	this->_prevKeyboard.fill(0);
	std::cout << "InputSDL created" << std::endl;
}

InputSDL::~InputSDL()
{
	std::cout << "InputSDL deleted" << std::endl;
}

void	InputSDL::update()
{
	if (this->_keyboard)
	{
		std::memcpy(
			this->_prevKeyboard.data(),
			this->_keyboard,
			SDL_NUM_SCANCODES
		);
	}
	SDL_PumpEvents();
	this->_keyboard = SDL_GetKeyboardState(NULL);
}

bool	InputSDL::isKeyPressed(SDL_Scancode code) const
{
	if (!this->_keyboard)
		return (false);
	return (this->_keyboard[code] && !this->_prevKeyboard[code]);
}

bool	InputSDL::isKeyDown(SDL_Scancode code) const
{
	if (!this->_keyboard)
		return (false);
	return (this->_keyboard[code]);
}

bool	InputSDL::isKeyReleased(SDL_Scancode code) const
{
	if (!this->_keyboard)
		return (false);
	return (
		!this->_keyboard[code]
		&& this->_prevKeyboard[code]
	);
}