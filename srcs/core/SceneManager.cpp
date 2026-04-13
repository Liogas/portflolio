#include "SceneManager.hpp"

SceneManager::SceneManager(RessourceManager &ressources):
	_currScene(nullptr),
	_ressources(ressources)
{
	std::cout << "SceneManager created" << std::endl;
};

SceneManager::~SceneManager()
{
	std::cout << "SceneManager destroyed" << std::endl;
}

void	SceneManager::render(RendererSDL &renderer, const GameState &gameState)
{
	this->_currScene->render(renderer, gameState);
}

void	SceneManager::update(InputSDL &input, const GameState &gameState, float deltaTime)
{
	this->_currScene->update(input, gameState, deltaTime);
}

void	SceneManager::changeScene(std::unique_ptr<Scene> scene, const GameState &gameState)
{
	if (this->_currScene)
		this->_currScene->onExit();
	this->_currScene = std::move(scene);
	if (this->_currScene)
		this->_currScene->onEnter(this->_ressources, gameState);
	else
		std::cout << "Probleme lors du changement de scene" << std::endl;
}

void	SceneManager::handleEvent(EventSDL &event, const GameState &gameState)
{
	this->_currScene->handleEvents(event, gameState);
}