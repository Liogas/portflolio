#ifndef SCENE_HPP
# define SCENE_HPP

# include <iostream>
# include <vector>

// ECS
# include <entt/entt.hpp>

// COMPOSANTS
# include "Position.hpp"
# include "Movement.hpp"
# include "PlayerTag.hpp"

# include "World.hpp"

// SDL
# include "AppSDL.hpp"
# include "EventSDL.hpp"
# include "InputSDL.hpp"
# include "RendererSDL.hpp"

class RessourceManager;

class Scene
{
	public:
		virtual 		~Scene() = default;
		// METHODS
		virtual void	load(World &world) 		= 0;
		virtual void	unload(World &world) 	= 0;
		
		// virtual void	onEnter(RessourceManager &ressources)	= 0;
		// virtual void	onExit()								= 0;
		// virtual void	update(InputSDL &inputs, const GameState &gameState, float deltaTime) 		= 0;
		// virtual void	handleEvents(EventSDL &, const GameState &gameState)						= 0;
		// virtual void	render(RendererSDL &, const GameState &gameState) 							= 0;
		// GETTERS
		[[nodiscard]] int	getHeight() const { return (this->_height); }
		[[nodiscard]] int	getWidth() const { return (this->_width); }
	protected:
		int 	_height;
		int		_width;
};

#endif