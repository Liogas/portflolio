#ifndef	INPUTSDL_HPP
# define INPUTSDL_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <stdexcept>

class InputSDL
{
	public:
		InputSDL();
		~InputSDL();
		InputSDL(const InputSDL &) = delete;
		InputSDL &operator=(const InputSDL &) = delete;
		void	update();
		bool	isKeyPressed(SDL_Scancode);
	private:
		Uint8	*_keyboard;
};

#endif