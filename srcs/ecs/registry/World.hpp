#ifndef WORLD_HPP
# define WORLD_HPP

# include <entt/entt.hpp>
# include <iostream>

# include "InputSDL.hpp"
# include "RendererSDL.hpp"

# include "RessourceManager.hpp"
# include "Camera.hpp"

# include "PlayerFactories.hpp"

# include "Scene.hpp"

# include "Position.hpp"

// SYSTEMS
# include "MovementSystem.hpp"
# include "InputSystem.hpp"
# include "CollisionSystem.hpp"
# include "AnimationStateSystem.hpp"
# include "AnimationSystem.hpp"
# include "InteractionSystem.hpp"
# include "RenderSystem.hpp"
# include "DebugRenderSystem.hpp"

class Scene;

class World
{
	public:
		World(RessourceManager &rm);
		// GETTERS
		[[nodiscard]] entt::registry	&getRegistry();
		[[nodiscard]] RessourceManager	&getRm();
		// SETTERS
		void	setMap(std::unique_ptr<TileMap> map);
		// METHODS
		void	update(InputSDL &input, float dt);
		void	render(RendererSDL &renderer);
		void	changeScene(std::unique_ptr<Scene> scene);
		void	updateCamera();
		void	toggleDebug();
		// PROPS
		bool	debug;
	private:
		entt::registry				_registry;
		RessourceManager			&_rm;
		std::unique_ptr<TileMap>	_map;
		std::unique_ptr<Scene> 		_scene;
		Camera						_camera;
		entt::entity				_player;
};

#endif