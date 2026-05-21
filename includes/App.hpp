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

# include "SceneManager.hpp"
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
	private:
		bool				_running;
		AppSDL				_sdl;
		WindowSDL			_window;
		RendererSDL			_renderer;
		InputSDL			_input;
		EventSDL			_event;
		RessourceManager	_rm;
		SceneManager		_sm;
		World				_world;
		void	handleEvents();
};

#endif