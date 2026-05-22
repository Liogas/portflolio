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

RessourceManager	&World::getRm()
{
	return (this->_rm);
}

void	World::update(InputSDL &input, float dt)
{
	InputSystem(this->_registry, input);
	MovementSystem(this->_registry);
	if (this->_map)
		CollisionSystem(this->_registry, *this->_map, dt);
	AnimationStateSystem(this->_registry);
	AnimationSystem(this->_registry, dt);
	// InteractionSystem(this->_registry);
}

void	World::render()
{
	RenderSystem(this->_registry);
}

void	World::init()
{
	try
	{
		PlayerFactories::create(this->_registry, this->_rm, 550.f, 280.f, "char1.png");
	} catch (const std::exception &e)
	{
		throw (std::runtime_error(std::string("ERROR World::init() -> ") + e.what()));
	}
}

void	World::setMap(std::unique_ptr<TileMap> map)
{
	this->_map = std::move(map);
}
