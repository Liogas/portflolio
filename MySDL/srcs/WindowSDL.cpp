#include "WindowSDL.hpp"

WindowSDL::WindowSDL(
	const char		*title,
	int				width,
	int				height,
	EWindowOption	option
)
{
	this->_window = SDL_CreateWindow(
		title,
		0,
		0,
		width,
		height,
		static_cast<Uint32>(option)
	);
	if (!this->_window)
		throw	std::runtime_error(SDL_GetError());
	this->_fullScreen = false;
	std::cout << "Window " << title << " created" << std::endl;
}

WindowSDL::~WindowSDL()
{
	if (this->_window)
	{
		std::cout << "Window " << SDL_GetWindowTitle(this->_window);
		std::cout << " destroyed" << std::endl;
		SDL_DestroyWindow(this->_window);
	}
}

void	WindowSDL::setFullScreen()
{
	if (!this->_window)
		std::cerr << "No window" << std::endl;
	if (!this->_fullScreen)
	{
		SDL_SetWindowFullscreen(this->_window, SDL_WINDOW_FULLSCREEN);
		this->_fullScreen = true;
	}
	else
	{
		SDL_SetWindowFullscreen(this->_window, 0);
		this->_fullScreen = false;
	}
}

SDL_Window	*WindowSDL::getWindow() const
{
	return (this->_window);
}