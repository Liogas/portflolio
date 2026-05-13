#ifndef SCENE_HPP
# define SCENE_HPP

# include "Position.hpp"
# include "Movement.hpp"
# include "PlayerTag.hpp"
# include <entt/entt.hpp>
# include <iostream>

# include "AppSDL.hpp"
# include "EventSDL.hpp"
# include "InputSDL.hpp"
# include "RendererSDL.hpp"
# include "GameState.hpp"
# include "Camera.hpp"
# include "Entity.hpp"

# include <vector>

class GameState;
class RessourceManager;
class Entity;

class Scene
{
	public:
		virtual 		~Scene() = default;
		// METHODS
		virtual void	load(entt::registry &registry, RessourceManager &ressources) = 0;
		virtual void	unload(entt::registry &registry) = 0;


		
		virtual void	onEnter(RessourceManager &ressources, const GameState &gameState) 			= 0;
		virtual void	onExit() 																	= 0;
		virtual void	update(InputSDL &inputs, const GameState &gameState, float deltaTime) 		= 0;
		virtual void	handleEvents(EventSDL &, const GameState &gameState)						= 0;
		virtual void	render(RendererSDL &, const GameState &gameState) 							= 0;
		void			addEntity(std::unique_ptr<Entity> e) {
			this->_entities.push_back(std::move(e));
		}
		// GETTERS
		[[nodiscard]] int	getHeight() const { return (this->_height); }
		[[nodiscard]] int	getWidth() const { return (this->_width); }
	protected:
		int 	_height;
		int		_width;
		Camera	_camera;
		std::vector<std::unique_ptr<Entity>> _entities;
};

#endif