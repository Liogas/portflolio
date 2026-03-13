#ifndef APP_HPP
# define APP_HPP

# include <iostream>
# include <stdexcept>
# include <chrono>
# include <thread>

# include "AppSDL.hpp"
# include "WindowSDL.hpp"
# include "EventSDL.hpp"
# include "InputSDL.hpp"
# include "RendererSDL.hpp"

# include "Sprite.hpp"
# include "RessourceManager.hpp"
# include "Player.hpp"
# include "SceneManager.hpp"
# include "GameState.hpp"

// SCENES
# include "GameScene.hpp"

class App
{
	public:
		App();
		~App();
		void	run();
	private:
		bool				_running;
		AppSDL				_sdl;
		WindowSDL			_window;
		RendererSDL			_renderer;
		InputSDL			_input;
		EventSDL			_event;
		RessourceManager	_ressources;
		SceneManager		_sceneManager;
		GameState			_gameState;
		void	handleEvents();
};

#endif