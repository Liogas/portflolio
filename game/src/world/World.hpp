#ifndef WORLD_HPP
# define WORLD_HPP

# include <iostream>

// MYSDL
# include "InputSDL.hpp"

// MANAGERS
# include "resources/ResourceManager.hpp"
# include "projects/ProjectManager.hpp"
# include "ui/manager/UIManager.hpp"

# include "graphics/Camera.hpp"
# include "scene/Scene.hpp"
# include "ecs/components/Position.hpp"

// UI
# include "ui/manager/UIManager.hpp"

// FACTORIES
# include "ecs/factories/PlayerFactories.hpp"

// EVENT
# include "ecs/events/InteractionModule.hpp"

// SYSTEMS
# include "ecs/systems/MovementSystem.hpp"
# include "ecs/systems/InputSystem.hpp"
# include "ecs/systems/CollisionSystem.hpp"
# include "ecs/systems/AnimationStateSystem.hpp"
# include "ecs/systems/AnimationSystem.hpp"
# include "ecs/systems/InteractionSystem.hpp"
# include "ecs/systems/RenderSystem.hpp"
# include "ecs/systems/DebugRenderSystem.hpp"
# include "ecs/systems/PylonSystem.hpp"
# include "ecs/systems/TriggerSystem.hpp"

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