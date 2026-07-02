#ifndef WORLD_HPP
# define WORLD_HPP

# include <iostream>

// MYSDL
# include "InputSDL.hpp"

// MANAGERS
# include "resources/ResourceManager.hpp"
# include "src/projects/ProjectManager.hpp"
# include "ui/manager/ComputerManager.hpp"

# include "graphics/Camera.hpp"
# include "scene/Scene.hpp"
# include "ecs/components/Position.hpp"

// UI
# include "UIManager.hpp"

// FACTORIES
# include "ecs/factories/PlayerFactories.hpp"

// EVENT
# include "events/InteractionModule.hpp"

// SYSTEMS
# include "MovementSystem.hpp"
# include "InputSystem.hpp"
# include "CollisionSystem.hpp"
# include "ecs/systems/AnimationStateSystem.hpp"
# include "AnimationSystem.hpp"
# include "InteractionSystem.hpp"
# include "RenderSystem.hpp"
# include "DebugRenderSystem.hpp"

# include "scene/SceneContext.hpp"

class World
{
	public:
		World(
			entt::registry		&registry,
			entt::dispatcher	&dispatcher,
			ResourceManager		&rm,
			ComputerManager 	&cm,
			ProjectManager 		&pm,
			RendererSDL			&renderer
		);
		// GETTERS
		[[nodiscard]] entt::registry			&getRegistry();
		[[nodiscard]] ResourceManager			&getRm();
		[[nodiscard]] ComputerManager			&getCm();
		[[nodiscard]] ProjectManager			&getPm();
		// SETTERS
		void	setMap(std::unique_ptr<TileMap> map);
		// METHODS
		void	update(InputSDL &input, float dt, RendererSDL &renderer);
		void	render(RendererSDL &renderer);
		void	changeScene(std::unique_ptr<Scene> scene);
		void	updateCamera();
		void	toggleDebug();
		// PROPS
		bool		debug;
	private:
		ControlsConfig							_cfg;
		entt::registry							&_registry;
		entt::dispatcher						&_dispatcher;
		ResourceManager							&_rm;
		ProjectManager							&_pm;
		ComputerManager							&_cm;
		UIManager								_UIm;
		std::unique_ptr<TileMap>				_map;
		std::unique_ptr<Scene> 					_scene;
		Camera									_camera;
		entt::entity							_player;
		InteractionModule						_interaction;
};

#endif