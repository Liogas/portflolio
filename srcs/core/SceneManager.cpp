#include "SceneManager.hpp"

SceneManager::SceneManager(RessourceManager &rm):
	_currScene(nullptr),
	_rm(rm)
{
	std::cout << "SceneManager created" << std::endl;
};

SceneManager::~SceneManager()
{
	std::cout << "SceneManager destroyed" << std::endl;
}

void	SceneManager::changeScene(std::unique_ptr<Scene> scene, World &world)
{
	if (this->_currScene)
		this->_currScene->load(world);
	this->_currScene = std::move(scene);
	if (this->_currScene)
		this->_currScene->unload(world);
	else
		std::cout << "Probleme lors du changement de scene" << std::endl;
}
