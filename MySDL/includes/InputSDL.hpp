#ifndef	INPUTSDL_HPP
# define INPUTSDL_HPP

# include <array>
# include <cstring>

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
		bool	isKeyPressed(SDL_Scancode) const;
		bool	isKeyDown(SDL_Scancode) const;
		bool	isKeyReleased(SDL_Scancode) const;
	private:
		const Uint8	*_keyboard;
		std::array<Uint8, SDL_NUM_SCANCODES> _prevKeyboard;
};

#endif