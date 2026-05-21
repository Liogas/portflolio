#include "TestScene.hpp"

TestScene::TestScene(int width, int height)
{
	this->_width =  width;
	this->_height = height;
	this->_map = nullptr;
    std::cout << "TestScene created" << std::endl;
}

void	TestScene::load(World &world)
{
	try
	{
		std::string path = world.getRm().getAssetsPath() + "maps/";
		MapParseur	parseur(path + "home.tmj");
		world.setMap(std::move(parseur.start(world)));
	} catch (const std::exception& e)
	{
		std::cerr << "ERROR TestScene::load" << std::endl;
		throw (std::runtime_error(e.what()));
	}
}

void	TestScene::unload(entt::registry &registry)
{

}