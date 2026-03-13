#include "SceneManager.hpp"

SceneManager::SceneManager():
	_currScene(nullptr)
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

void	SceneManager::update(InputSDL &input, const GameState &gameState)
{
	this->_currScene->update(input, gameState);
}

void	SceneManager::changeScene(std::unique_ptr<Scene> scene)
{
	if (this->_currScene)
		this->_currScene->onExit();
	this->_currScene = std::move(scene);
	if (this->_currScene)
		this->_currScene->onEnter();
	else
		std::cout << "Probleme lors du changement de scene" << std::endl;
}

void	SceneManager::handleEvent(EventSDL &event, const GameState &gameState)
{
	this->_currScene->handleEvents(event, gameState);
}