#include "MapParseur.hpp"

MapParseur::MapParseur(const std::string &path)
{
	std::cout << "MapParseur created" << std::endl;
	std::filesystem::path p(path);
	if (p.extension() != ".json" && p.extension() != ".tmj")
		throw std::runtime_error("Bad extension");
}

MapParseur::~MapParseur()
{
	std::cout << "MapParseur destroyed" << std::endl;
}

TileMap	*MapParseur::start()
{
	throw std::runtime_error("WIP");
}