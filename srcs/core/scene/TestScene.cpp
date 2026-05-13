#include "TestScene.hpp"

TestScene::TestScene(int width, int height)
{
	this->_width =  width;
	this->_height = height;
	this->_map = nullptr;
    std::cout << "TestScene created" << std::endl;
}

void	TestScene::load(entt::registry &registry, RessourceManager &ressources)
{
	try
	{
		std::string path = ressources.getAssetsPath() + "maps/";
		MapParseur	parseur(path + "home.tmj");
		this->_map = parseur.start(ressources, registry);


	} catch (const std::exception& e)
	{
		std::cerr << "ERROR TestScene::load" << std::endl;
		throw (std::runtime_error(e.what()));
	}
}

void	TestScene::unload(entt::registry &registry)
{

}