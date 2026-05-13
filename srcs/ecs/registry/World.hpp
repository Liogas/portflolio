#ifndef WORLD_HPP
# define WORLD_HPP

# include <entt/entt.hpp>
# include "MovementSystem.hpp"
# include "InputSystem.hpp"
# include "InputSDL.hpp"
# include <iostream>

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