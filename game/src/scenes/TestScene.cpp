#include "TestScene.hpp"

TestScene::TestScene(int width, int height)
{
	this->_width =  width;
	this->_height = height;
    std::cout << "TestScene created" << std::endl;
}

void	TestScene::load(SceneContext &ctx)
{
	try
	{
		std::string path = ctx.resources.getAssetsPath() + "maps/hubtest.tmj";
		ctx.map = MapParser::start(path, ctx.registry, ctx.resources);
	} catch (const std::exception& e)
	{
		std::cerr << "ERROR TestScene::load" << std::endl;
		throw (std::runtime_error(e.what()));
	}
}

void	TestScene::unload(SceneContext &ctx)
{
	std::cout << "TestScene::unload WIP" << std::endl;
}