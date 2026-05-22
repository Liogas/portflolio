#include "World.hpp"

World::World(RessourceManager &rm):
	_rm(rm),
	_map(nullptr)
{
	this->_player = PlayerFactories::create(
		this->_registry, this->_rm, 550.f, 280.f, "char1.png"
	);
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
	CollisionSystem(this->_registry, *this->_map, dt);
	AnimationStateSystem(this->_registry);
	AnimationSystem(this->_registry, dt);
	// InteractionSystem(this->_registry);
	this->updateCamera();
}

void	World::updateCamera()
{
	auto &pos = this->_registry.get<Position>(this->_player);
	this->_camera.setPos(
		pos.x - this->_scene->getWidth() / 4,
		pos.y - this->_scene->getHeight() / 4
	);
}

void	World::render()
{
	if (this->_map)
		this->_map->render(this->_camera);
	RenderSystem(this->_registry, this->_camera);
}

void	World::setMap(std::unique_ptr<TileMap> map)
{
	this->_map = std::move(map);
}

void	World::changeScene(std::unique_ptr<Scene> scene)
{
	if (this->_scene)
		this->_scene->unload(*this);
	this->_scene = std::move(scene);
	this->_scene->load(*this);
}
