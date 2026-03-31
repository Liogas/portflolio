#ifndef MAPPARSEUR_HPP
# define MAPPARSEUR_HPP

# include <iostream>
# include <filesystem>
# include <fstream>
# include "tinyxml2.h"
# include "TileMap.hpp"
# include "json.hpp"

typedef struct s_tileset
{
	int			firstgid;
	std::string pathfile;
}	t_tileset;

typedef struct	s_layer
{
	std::vector<int>	data;
	bool				visible;
	std::string			name;
}	t_layer;

class MapParseur
{
	public:
		MapParseur(const std::string &path);
		~MapParseur();
		TileMap	*start();
	private:
		// PROPS
		std::string				_path;
		std::vector<t_tileset>	_tilesets;
		std::vector<t_layer>	_layers;
		
		// METHODS
		void	loadTilesets(nlohmann::json &data);
		void	loadLayers(nlohmann::json &data);
};

#endif