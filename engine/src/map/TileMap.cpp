#include "map/TileMap.hpp"

TileMap::TileMap()
{
	this->_height = 0;
	this->_width = 0;
	std::cout << "TileMap created" << std::endl;
}

TileMap::~TileMap()
{
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

const t_tileset	*TileMap::getTilesetByPath(const std::string path)
{
	for (const auto &ts : this->_tilesets)
	{
		if (ts.pathfile == path)
			return (&ts);
	}
	throw std::runtime_error("ERROR getTilesetByPath : not found");
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

std::vector<CollisionShape>	TileMap::getWorldCollisionShapes(const SDL_Rect &area) const
{
	std::vector<CollisionShape> result;
	int	startTileX = area.x / this->_tileSize;
	int endTileX = (area.x + area.w - 1) / this->_tileSize;

	int	startTileY = area.y / this->_tileSize;
	int endTileY = (area.y + area.h - 1) / this->_tileSize;

	for (int ty = startTileY; ty <= endTileY; ++ty)
	{
		for (int tx = startTileX; tx <= endTileX; ++tx)
		{
			if (tx < 0 || ty < 0 || tx >= this->_width || ty >= this->_height)
				continue ;
			for (const auto &layer : this->_layers)
			{
				int gid = layer.data[ty * this->_width + tx];
				if (gid == 0)
					continue ;
				const t_tileset *ts = getTilesetForTile(gid);
				if (!ts)
					continue ;
				int localId = gid - ts->firstgid;
				auto it = ts->collisions.find(localId);
				if (it == ts->collisions.end())
					continue ;
				for (const auto &shape : it->second)
				{
					CollisionShape world = shape; // copie polygon ET triangles
					if (world.type == CollisionShapeType::Rect)
					{
						world.rect.x += tx * ts->tileWidth;
						world.rect.y += ty * ts->tileHeight;
					}
					else
					{
						int offX = tx * ts->tileWidth;
						int offY = ty * ts->tileHeight;

						// Translate le polygon - OK deja fait
						for (auto &p : world.polygon)
						{
							p.x += offX;
							p.y += offY;
						}

						// Translate aussi les triangles precalcules - MANQUANT
						for (auto &tri : world.triangles)
							for (auto &p : tri)
							{
								p.x += offX;
								p.y += offY;
							}
					}
					result.push_back(std::move(world));
				}
			}
		}
	}
	return (result);
}

void    TileMap::debugPrint() const
{
    std::cout << "TileMap: " << _width << "x" << _height
              << " tileSize=" << _tileSize
              << " tilesets=" << _tilesets.size()
              << " layers=" << _layers.size() << std::endl;
    for (const auto &ts : _tilesets)
        std::cout << "  Tileset firstgid=" << ts.firstgid
                  << " cols=" << ts.columns
                  << " path=" << ts.pathfile << std::endl;
    for (const auto &l : _layers)
        std::cout << "  Layer: " << l.name
                  << " data.size()=" << l.data.size()
                  << " visible=" << l.visible << std::endl;
}