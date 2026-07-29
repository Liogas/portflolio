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
		// void	init();
		// void	onQuit(const QuitGameEvent &e);
	private:
		// bool				_running;
		AppSDL				_sdl;
		WindowSDL			_window;
		RendererSDL			_renderer;
		// InputSDL			_input;
		// EventSDL			_event;
		// ResourceManager		_rm;
		// ProjectManager		_pm;
		// ComputerManager		_cm;
		entt::registry		_registry;
		// entt::dispatcher	_dispatcher;
		// World				_world;
		// void	handleEvents();
};

#endif