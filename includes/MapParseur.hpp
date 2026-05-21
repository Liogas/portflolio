#ifndef MAPPARSEUR_HPP
# define MAPPARSEUR_HPP

# include <iostream>
# include <filesystem>
# include <fstream>

# include "TileMap.hpp"
# include "RessourceManager.hpp"
# include "Computer.hpp"
# include "Scene.hpp"

# include "tinyxml2.h"
# include "json.hpp"

# include "ComputerFactories.hpp"

class MapParseur
{
	public:
		std::unique_ptr<TileMap> start(
			const std::string &path,
			World	&world
		);
};

#endif