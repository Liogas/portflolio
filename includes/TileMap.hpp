#ifndef TILEMAP_HPP
# define TILEMAP_HPP

# include <iostream>
# include <vector>

# include "TextureSDL.hpp"

/*
	Regle pour les layers
	PASSAGES -> collisions
	INTERACTIVE -> case avec interaction
	other -> texture simple pour le moment
*/

typedef struct s_tileset
{
	int			firstgid;
	int			tileWidth;
	int			tileHeight;
	int			columns;
	TextureSDL	texture;
	std::string pathfile;
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
		// SETTERS
		void	setWidth(int w);
		void	setHeight(int h);
		void	setTileSize(int s);
		void	setCollisionLayer(t_layer l);
		// GETTERS
		[[nodiscard]] int	getWidth() const;
		[[nodiscard]] int	getHeight() const;
		[[nodiscard]] int	getTileSize() const;
	private:
		int						_width;
		int						_height;
		int						_tileSize;
		std::vector<t_tileset>	_tilesets;
		std::vector<t_layer>	_layers;
		t_layer					_collisionLayer;
};

#endif