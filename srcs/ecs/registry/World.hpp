#ifndef WORLD_HPP
# define WORLD_HPP

# include <entt/entt.hpp>
# include <iostream>

# include "InputSDL.hpp"

# include "SceneManager.hpp"
# include "RessourceManager.hpp"
# include "Camera.hpp"

# include "PlayerFactories.hpp"

// SYSTEMS
# include "MovementSystem.hpp"
# include "InputSystem.hpp"
# include "CollisionSystem.hpp"
# include "AnimationStateSystem.hpp"
# include "AnimationSystem.hpp"
# include "InteractionSystem.hpp"
# include "RenderSystem.hpp"

class SceneManager;

class World
{
	public:
		World(RessourceManager &rm, SceneManager &sm);
		// GETTERS
		[[nodiscard]] entt::registry	&getRegistry();
		[[nodiscard]] RessourceManager	&getRm();
		// SETTERS
		void	setMap(std::unique_ptr<TileMap> map);
		// METHODS
		void	init();
		void	update(InputSDL &input, float dt);
		void	render();
	private:
		entt::registry				_registry;
		RessourceManager			&_rm;
		SceneManager				&_sm;
		std::unique_ptr<TileMap>	_map;
};

#endif