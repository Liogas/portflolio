#ifndef WORLD_HPP
# define WORLD_HPP

# include <entt/entt.hpp>
# include "MovementSystem.hpp"
# include <iostream>

class World
{
	public:
		World();
		// GETTERS
		[[nodiscard]] entt::registry	&getRegistry();
		// METHODS
		void	update(float dt);
	private:
		entt::registry	_registry;
};

#endif