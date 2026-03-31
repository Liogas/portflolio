#include "TileMap.hpp"

TileMap::TileMap(int width, int height)
{
	this->_height = height;
	this->_width = width;
	std::cout << "TileMap created" << std::endl;
}

TileMap::~TileMap()
{
	std::cout << "TileMap destroyed" << std::endl;
}

void	TileMap::setHeight(int h)
{
	this->_height = h;
}

void	TileMap::setWidth(int w)
{
	this->_width = w;
}

void	TileMap::setTileSize(int s)
{
	this->_tileSize = s;
}


int	TileMap::getHeight() const
{
	return (this->_height);
}

int	TileMap::getWidth() const
{
	return (this->_width);
}

int	TileMap::getTileSize() const
{
	return (this->_tileSize);
}