#include "map/TileMap.hpp"

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

std::vector<SDL_Rect>	TileMap::getCollisionRects(int gid, int tileX, int tileY) const
{
	if (gid <= 0)
		return ({});
	const t_tileset	*found = nullptr;
	for (const auto &ts : this->_tilesets)
		if (ts.firstgid <= gid)
			found = &ts;
	if (!found)
		return ({});
	int localId = gid - found->firstgid;
	auto it = found->collisions.find(localId);
	if (it == found->collisions.end())
		return ({});
	std::vector<SDL_Rect> world;
	int worldX = tileX * found->tileWidth;
	int worldY = tileY * found->tileHeight;
	for (const auto &r : it->second)
	{
		world.push_back({
			worldX + r.x,
			worldY + r.y,
			r.w,
			r.h
		});
	}
	return (world);
}

void	TileMap::markTileUnwalkable(int tileX, int tileY)
{
	if (tileX < 0 || tileY < 0 || tileX >= this->_width || tileY >= this->_height)
		return ;
	this->_walkabilityGrid[tileY * this->_width + tileX] = false;
}

void    TileMap::initWalkabilityGrid(int w, int h)
{
    this->_width  = w;
    this->_height = h;
    this->_walkabilityGrid.assign(w * h, true);
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

bool	TileMap::isWalkable(float x, float y, int w, int h) const
{
	int tileSize = this->_tileSize;
	int corners[4][2] = {
		{ (int)x, (int)y },
		{ (int)(x + w), (int)y },
		{ (int)x, (int)(y + h) },
		{ (int)(x + w), (int)(y + h) }
	};
	for (auto &c : corners)
	{
		int tx = c[0] / tileSize;
		int ty = c[1] / tileSize;
		if (tx < 0 || ty < 0 || tx >= this->_width || ty >= this->_height)
			return (false);
		if (!this->_walkabilityGrid[ty * this->_width + tx])
			return (false);
	}
	return (true);
}
