#include "World.hpp"

World::World(RessourceManager &rm, SceneManager &sm):
	_rm(rm),
	_sm(sm),
	_map(nullptr)
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
	CollisionSystem(this->_registry);
	AnimationSystem(this->_registry);
	InteractionSystem(this->_registry);
}

void	World::render()
{
	std::cout << "WIP" << std::endl;
	RenderSystem(this->_registry);
}

void	World::init()
{
	try
	{
		auto player = PlayerFactories::create(registry, 550.f, 280.f, "char1.png");
	} catch (const std::exception &e)
	{
		throw (std::runtime_error("ERROR World::init() -> " + e.what()));
	}
}