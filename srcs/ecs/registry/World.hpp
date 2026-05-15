#ifndef WORLD_HPP
# define WORLD_HPP

# include <entt/entt.hpp>
# include "InputSDL.hpp"
# include <iostream>

// SYSTEMS
# include "MovementSystem.hpp"
# include "InputSystem.hpp"
# include "CollisionSystem.hpp"
# include "AnimationSystem.hpp"
# include "InteractionSystem.hpp"

class World
{
	public:
		World();
		// GETTERS
		[[nodiscard]] entt::registry	&getRegistry();
		// METHODS
		void	update(InputSDL input, float dt);
		void	render();
	private:
		entt::registry	_registry;
};

#endif