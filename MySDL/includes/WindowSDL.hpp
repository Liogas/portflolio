#ifndef WINDOWSDL_HPP
# define WINDOWSDL_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <stdexcept>

enum class EWindowOption : Uint32
{
	FULLSCREEN		= SDL_WINDOW_FULLSCREEN,
	OPENGL			= SDL_WINDOW_OPENGL,
	SHOWN			= SDL_WINDOW_SHOWN,
	HIDDEN			= SDL_WINDOW_HIDDEN,
	BORDERLESS		= SDL_WINDOW_BORDERLESS,
	RESIZABLE		= SDL_WINDOW_RESIZABLE,
	MINIMIZED		= SDL_WINDOW_MINIMIZED,
	MAXIMIZED		= SDL_WINDOW_MAXIMIZED,
	INPUT_GRABBED	= SDL_WINDOW_INPUT_GRABBED,
	INPUT_FOCUS		= SDL_WINDOW_INPUT_FOCUS,
	MOUSE_FOCUS		= SDL_WINDOW_MOUSE_FOCUS,
	FOREIGN			= SDL_WINDOW_FOREIGN
};

inline EWindowOption operator|(EWindowOption a, EWindowOption b)
{
    return static_cast<EWindowOption>(
        static_cast<Uint32>(a) | static_cast<Uint32>(b)
    );
}

class WindowSDL
{
	public:
		WindowSDL(const char *, int, int, EWindowOption);
		~WindowSDL(void);
		WindowSDL(const WindowSDL &) = delete;
		WindowSDL &operator=(const WindowSDL &) = delete;
		// GETTERS
		SDL_Window	*getWindow() const;

		void	setFullScreen();
	private:
		SDL_Window	*_window;
		bool		_fullScreen;
};

#endif