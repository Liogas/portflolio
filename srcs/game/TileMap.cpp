#include "TileMap.hpp"

TileMap::TileMap(const std::string &path_file)
{
	std::cout << "TileMap created with " << path_file << std::endl;
}

TileMap::~TileMap()
{
	std::cout << "TileMap destroyed" << std::endl;
}
