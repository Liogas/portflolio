#include "World.hpp"

World::World(
	entt::registry		&registry,
	entt::dispatcher	&dispatcher,
	RessourceManager 	&rm, 
	ComputerManager 	&cm,
	ProjectManager 		&pm,
	RendererSDL			&renderer
):
	_registry(registry),
	_dispatcher(dispatcher),
	_rm(rm),
	_pm(pm),
	_cm(cm),
	_UIm(this->_cm, this->_pm, this->_rm, renderer, this->_dispatcher, this->_cfg),
	_map(nullptr),
	_interaction(this->_registry, this->_dispatcher)
{
	this->_player = PlayerFactories::create(
		this->_registry, this->_rm, 550.f, 280.f, "char1.png"
	);
	this->debug = false;
	this->_UIm.bind(this->_dispatcher);
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

ComputerManager	&World::getCm()
{
	return (this->_cm);
}

ProjectManager	&World::getPm()
{
	return (this->_pm);
}

void	World::update(InputSDL &input, float dt, RendererSDL &renderer)
{
	(void)renderer;
	this->_UIm.handleInput(input);
	this->_UIm.update(dt);
	if (!this->_UIm.blocksGameplay())
	{
		if (input.isKeyPressed(SDL_SCANCODE_ESCAPE))
            this->_dispatcher.trigger(OpenPauseMenuEvent{});
		InputSystem(*this, this->_registry, input, this->_cfg);
		MovementSystem(this->_registry);
		CollisionSystem(this->_registry, *this->_map, dt);
		InteractionSystem(*this, this->_registry, input, this->_dispatcher);
		AnimationStateSystem(this->_registry);
		AnimationSystem(this->_registry, dt);
		this->updateCamera();
	}
}

void	World::toggleDebug()
{
	this->debug = !this->debug;
}

void	World::updateCamera()
{
	auto &pos = this->_registry.get<Position>(this->_player);
	this->_camera.setPos(
		pos.x - this->_scene->getWidth() / 4,
		pos.y - this->_scene->getHeight() / 4
	);
}

void	World::render(RendererSDL &renderer)
{
	if (this->_map)
		this->_map->render(this->_camera);
	RenderSystem(this->_registry, this->_camera);
	if (this->debug)
		DebugRenderSystem(this->_registry, renderer, this->_camera);
	this->_UIm.render(renderer);
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

