#include "TileMap.hpp"

TileMap::TileMap()
{
	this->_height = 0;
	this->_width = 0;
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

void	TileMap::setCollisionLayer(t_layer l)
{
	this->_collisionLayer = l;
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

t_layer	TileMap::getCollisionLayer() const
{
	return (this->_collisionLayer);
}

void	TileMap::addLayer(t_layer l)
{
	this->_layers.push_back(l);
}

void	TileMap::addTileset(t_tileset t)
{
	this->_tilesets.push_back(t);
}

void	TileMap::printLayers()
{
	for (t_layer l : this->_layers)
		std::cout << "Layer : " << l.name << std::endl;
}

void	TileMap::render(Camera &camera)
{
	for (const auto &layer : this->_layers)
	{
		if (!layer.visible)
			continue ;
		for (int y = 0; y < this->_height; y++)
		{
			for (int x = 0; x < this->_width; x++)
			{
				int index = layer.data[y * this->_width + x];
				if (index == 0)
					continue ;
				const t_tileset *tileset = this->getTilesetForTile(index);
				int localId = index - tileset->firstgid;
				int tilesPerRow = tileset->columns;
				int srcX = (localId % tilesPerRow) * tileset->tileWidth;
				int srcY = (localId / tilesPerRow) * tileset->tileHeight;
				int dstX = x * this->_tileSize;
				int dstY = y * this->_tileSize;
				tileset->sprite->setSrcPosition(srcX, srcY);
				tileset->sprite->setDestPosition(dstX - camera.getX(), dstY - camera.getY());
				tileset->sprite->render();
			}
		}
	}
}

const t_tileset	*TileMap::getTilesetForTile(int gid) const
{
	const t_tileset	*ts = nullptr;
	for (const auto &tileset : this->_tilesets)
	{
		if (gid >= tileset.firstgid)
			ts = &tileset;
		else
			break ;
	}
	return (ts);
}

bool	TileMap::isWalkable(int x, int y, int w, int h) const
{
	int left = x / this->_tileSize;
	int right = (x + width - 1) / this->_tileSize;

	int top = y / this->_tileSize;
	int bottom = (y + height - 1) / this->_tileSize; 

	return (
		this->isTileWalkable(left, top)
		&& this->isTileWalkable(right, top)
		&& this->isTileWalkable(left, bottom)
		&& this->isTileWalkable(right, bottom)
	);
}

bool	TileMap::isTileWalkable(int tileX, int tileY) const
{
	if (tileX < 0 || tileX >= this->_width
		|| tileY >= this->_height || tileY < 0)
		return (false);
	int index = tileY * this->_width + tileX;
	return (this->_collisionLayer.data[index] == 0);
}


