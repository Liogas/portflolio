#include "World.hpp"

World::World(RessourceManager &rm, ComputerManager &cm, ProjectManager &pm):
	_rm(rm),
	_pm(pm),
	_cm(cm),
	_map(nullptr),
	_computerUI(std::nullopt)
{
	this->_player = PlayerFactories::create(
		this->_registry, this->_rm, 550.f, 280.f, "char1.png"
	);
	this->debug = false;
	this->gameState = GameState::Playing;
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

std::optional<ComputerUI>	&World::getComputerUI()
{
	return (this->_computerUI);
}

void	World::update(InputSDL &input, float dt)
{
	InputSystem(*this, this->_registry, input);
	MovementSystem(*this, this->_registry);
	CollisionSystem(this->_registry, *this->_map, dt);
	InteractionSystem(*this, this->_registry, input, this->_eventBus);
	GameplayEventSystem(*this, this->_registry, this->_eventBus);
	AnimationStateSystem(this->_registry);
	AnimationSystem(this->_registry, dt);
	this->updateCamera();
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
	if (this->_computerUI.has_value())
		UISystem(*this, renderer);
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

bool	World::isGameplayBlocked() const
{
	return (this->gameState != GameState::Playing);
}

void	World::setComputerUI(ComputerUI c)
{
	this->_computerUI = std::move(c);
}

void	World::openComputer(const std::string &id)
{
	ComputerUI	ui;

	auto &computerData = this->_cm.get(id);
	ui.title = computerData.title;
	for (auto &projectId : computerData.projectIds)
		ui.cards.push_back({&this->_pm.get(projectId),{}, false});
	ui.selectedCard = 0;
	this->_computerUI = std::move(ui);
	this->gameState = GameState::ComputerInteraction;
}

void	World::closeComputer()
{
	this->_computerUI.reset();
	this->gameState = GameState::Playing;
}

