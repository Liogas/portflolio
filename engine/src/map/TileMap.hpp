#ifndef TILEMAP_HPP
# define TILEMAP_HPP

# include <iostream>
# include <vector>
# include <memory>

# include "graphics/Sprite.hpp"
# include "graphics/Camera.hpp"

typedef struct s_tileset
{
	int						firstgid;
	int						tileWidth;
	int						tileHeight;
	int						columns;
	std::string 			pathfile;
	std::shared_ptr<Sprite>	sprite;
}	t_tileset;

typedef struct	s_layer
{
	std::vector<int>	data;
	bool				visible;
	std::string			name;
}	t_layer;

class TileMap
{
	public:
		TileMap();
		~TileMap();
		// METHODS
		void	addTileset(t_tileset);
		void	addLayer(t_layer);
		void	printLayers();
		void	render(Camera &camera);
		bool	isWalkable(int x, int y, int w, int h) const;
		// SETTERS
		void	setWidth(int w);
		void	setHeight(int h);
		void	setTileSize(int s);
		void	setCollisionLayer(t_layer l);
		// GETTERS
		[[nodiscard]] int		getWidth() const;
		[[nodiscard]] int		getHeight() const;
		[[nodiscard]] int		getTileSize() const;
		[[nodiscard]] t_layer	getCollisionLayer() const;
	private:
		// PROPS
		int						_width;
		int						_height;
		int						_tileSize;
		std::vector<t_tileset>	_tilesets;
		std::vector<t_layer>	_layers;
		t_layer					_collisionLayer;
		// METHODS
		const t_tileset	*getTilesetForTile(int gid) const;
		bool			isTileWalkable(int tileX, int tileY) const;
};

#endif