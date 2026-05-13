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

# include "World.hpp"

# include "Persistent.hpp"
# include "Velocity.hpp"
# include "Collider.hpp"

// FACTORIES
# include "PlayerFactories.hpp"

// SCENES
# include "GameScene.hpp"
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
		RessourceManager	_ressources;
		SceneManager		_sceneManager;
		GameState			_gameState;
		World				_world;
		void	handleEvents();
};

#endif