#ifndef MAPPARSEUR_HPP
# define MAPPARSEUR_HPP

# include <iostream>
# include <filesystem>
# include <fstream>

# include "TileMap.hpp"
# include "RessourceManager.hpp"

# include "tinyxml2.h"
# include "json.hpp"

class MapParseur
{
	public:
		MapParseur(const std::string &path);
		~MapParseur();
		std::unique_ptr<TileMap> start(RessourceManager &ressources);
	private:
		// PROPS
		std::string					_path;
		std::unique_ptr<TileMap>	_map;
		// METHODS
		void	parseTilesets(nlohmann::json &data, RessourceManager &ressources);
		void	parseLayers(nlohmann::json &data);
};

#endif