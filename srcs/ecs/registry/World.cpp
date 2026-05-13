#include "World.hpp"

World::World()
{
	std::cout << "World created" << std::endl;
}

entt::registry	&World::getRegistry()
{
	return (this->_registry);
}

void	World::update(InputSDL input, float dt)
{
	InputSystem(this->_registry, input);
	MovementSystem(this->_registry, dt);
}

void	World::render()
{
	std::cout << "WIP" << std::endl;
}