#ifndef WORLD_HPP
# define WORLD_HPP

# include <entt/entt.hpp>
# include <iostream>

// MYSDL
# include "InputSDL.hpp"
# include "RendererSDL.hpp"

// MANAGERS
# include "RessourceManager.hpp"
# include "ProjectManager.hpp"
# include "ComputerManager.hpp"

# include "Camera.hpp"
# include "Scene.hpp"
# include "Position.hpp"
# include "EventBus.hpp"

// FACTORIES
# include "PlayerFactories.hpp"

// SYSTEMS
# include "MovementSystem.hpp"
# include "InputSystem.hpp"
# include "CollisionSystem.hpp"
# include "AnimationStateSystem.hpp"
# include "AnimationSystem.hpp"
# include "InteractionSystem.hpp"
# include "RenderSystem.hpp"
# include "DebugRenderSystem.hpp"
# include "GameplayEventSystem.hpp"
# include "UISystem.hpp"

class Scene;

enum class GameState
{
	Playing,
	ComputerInteraction,
	Dialogue,
	Paused
};

class World
{
	public:
		World(RessourceManager &rm, ComputerManager &cm, ProjectManager &pm);
		// GETTERS
		[[nodiscard]] entt::registry	&getRegistry();
		[[nodiscard]] RessourceManager	&getRm();
		[[nodiscard]] ComputerManager	&getCm();
		[[nodiscard]] ProjectManager	&getPm();
		[[nodiscard]] entt::entity		&getActiveComputer();
		// SETTERS
		void	setMap(std::unique_ptr<TileMap> map);
		void	setActiveComputer(entt::entity e);
		// METHODS
		void	update(InputSDL &input, float dt);
		void	render(RendererSDL &renderer);
		void	changeScene(std::unique_ptr<Scene> scene);
		void	updateCamera();
		void	toggleDebug();
		bool	isGameplayBlocked() const;
		// PROPS
		bool		debug;
		GameState	gameState;
	private:
		entt::registry				_registry;
		RessourceManager			&_rm;
		ProjectManager				&_pm;
		ComputerManager				&_cm;
		std::unique_ptr<TileMap>	_map;
		std::unique_ptr<Scene> 		_scene;
		Camera						_camera;
		entt::entity				_player;
		EventBus					_eventBus;
		entt::entity				_activeComputer;
};

#endif