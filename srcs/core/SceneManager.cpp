#include "SceneManager.hpp"

SceneManager::SceneManager(RessourceManager &rm):
	_currScene(nullptr),
	_rm(ressources)
{
	std::cout << "SceneManager created" << std::endl;
};

SceneManager::~SceneManager()
{
	std::cout << "SceneManager destroyed" << std::endl;
}

void	SceneManager::render(RendererSDL &renderer)
{
	this->_currScene->render(renderer);
}

void	SceneManager::update(InputSDL &input, float deltaTime)
{
	this->_currScene->update(input, deltaTime);
}

void	SceneManager::changeScene(std::unique_ptr<Scene> scene)
{
	if (this->_currScene)
		this->_currScene->load();
	this->_currScene = std::move(scene);
	if (this->_currScene)
		this->_currScene->unload(this->_rm);
	else
		std::cout << "Probleme lors du changement de scene" << std::endl;
}

void	SceneManager::handleEvent(EventSDL &event)
{
	this->_currScene->handleEvents(event);
}