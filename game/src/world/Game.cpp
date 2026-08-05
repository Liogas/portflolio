#include "Game.hpp"
#include "scenes/TestScene.hpp"

Game::Game():
	_running(true)
{}

void Game::init(RendererSDL &renderer, entt::registry &registry)
{
	this->_rm = std::make_unique<ResourceManager>(renderer);
	this->_uim = std::make_unique<UIManager>(
		this->_cm, this->_pm, *this->_rm, renderer, this->_dispatcher, this->_cfg
	);
	this->_world = std::make_unique<World>(
		registry,
		this->_dispatcher,
		*this->_rm,
		this->_cm,
		this->_pm,
		renderer
	);
	this->_cm.loadAll();
	this->_pm.loadAll();
	this->_dispatcher.sink<QuitGameEvent>().connect<&Game::onQuit>(*this);
	this->_uim->bind(this->_dispatcher);
	this->_world->changeScene(std::make_unique<TestScene>(
		renderer.getWidth(), renderer.getHeight()
	));
}

void	Game::update(RendererSDL &renderer, InputSDL &input, float dt)
{
	if (input.isKeyPressed(SDL_SCANCODE_F3))
		this->_world->toggleDebug();
	this->_world->update(input, dt, renderer);
}

void	Game::render(RendererSDL &renderer)
{
	this->_world->render(renderer);
}
bool	Game::isRunning() const
{
	return (this->_running);
}

void	Game::onQuit(const QuitGameEvent &)
{
	this->_running = false;
}