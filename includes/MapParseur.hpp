#ifndef MAPPARSEUR_HPP
# define MAPPARSEUR_HPP

# include <iostream>
# include <filesystem>
# include "tinyxml2.h"
# include "TileMap.hpp"

class MapParseur
{
	public:
		MapParseur(const std::string &path);
		~MapParseur();
		TileMap	*start();
	private:

};

#endif