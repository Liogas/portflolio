#ifndef APP_HPP
# define APP_HPP

# include <iostream>
# include <stdexcept>
# include <chrono>
# include <thread>

# include "IGame.hpp"

// SDL
# include "AppSDL.hpp"
# include "WindowSDL.hpp"
# include "EventSDL.hpp"

class App
{
	public:
		App(int width, int height, const std::string &title);
		~App();
		void	run(std::unique_ptr<IGame> game);
	private:
		AppSDL				_sdl;
		WindowSDL			_window;
		RendererSDL			_renderer;
		entt::registry		_registry;
};

#endif