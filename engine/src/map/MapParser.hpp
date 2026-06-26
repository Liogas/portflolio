#ifndef MapParser_HPP
# define MapParser_HPP

# include <iostream>
# include <filesystem>
# include <fstream>

# include "TileMap.hpp"
# include "resources/ResourceManager.hpp"
# include "Computer.hpp"
# include "Scene.hpp"

# include "tinyxml2.h"
# include "json.hpp"

# include "factories/ComputerFactories.hpp"

class MapParser
{
	public:
		MapParser() = delete;
		static std::unique_ptr<TileMap> start(
			const std::string &path,
			World	&world
		);
};

#endif