#include "TestScene.hpp"

TestScene::TestScene(int width, int height)
{
	this->_width =  width;
	this->_height = height;
    std::cout << "TestScene created" << std::endl;
}

void	TestScene::load(World &world)
{
	try
	{
		std::string path = world.getRm().getAssetsPath() + "maps/";
		world.setMap(MapParser::start(path + "home.tmj", world));
	} catch (const std::exception& e)
	{
		std::cerr << "ERROR TestScene::load" << std::endl;
		throw (std::runtime_error(e.what()));
	}
}

void	TestScene::unload(World &world)
{
	(void) world;
	std::cout << "TestScene::unload WIP" << std::endl;
}