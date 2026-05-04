#include "World.hpp"

World::World()
{
	std::cout << "World created" << std::endl;
}

entt::registry	&World::getRegistry()
{
	return (this->_registry);
}

// void	World::update(float dt)
// {
// 	MovementSystem(registry, dt);
// }