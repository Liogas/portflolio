#ifndef APP_HPP
# define APP_HPP

# include <iostream>
# include <stdexcept>
# include <chrono>
# include <thread>

// SDL
# include "AppSDL.hpp"
# include "WindowSDL.hpp"
# include "EventSDL.hpp"
# include "InputSDL.hpp"
# include "RendererSDL.hpp"

# include "World.hpp"

// SCENES
# include "TestScene.hpp"

class App
{
	public:
		App();
		~App();
		void	run();
		void	init();
		void	onQuit(const QuitGameEvent &e);
	private:
		bool				_running;
		AppSDL				_sdl;
		WindowSDL			_window;
		RendererSDL			_renderer;
		InputSDL			_input;
		EventSDL			_event;
		ResourceManager	_rm;
		ProjectManager		_pm;
		ComputerManager		_cm;
		entt::registry		_registry;
		entt::dispatcher	_dispatcher;
		World				_world;
		void	handleEvents();
};

#endif