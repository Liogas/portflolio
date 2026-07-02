#ifndef MapParser_HPP
# define MapParser_HPP

# include <iostream>
# include <filesystem>
# include <fstream>

# include "map/TileMap.hpp"
# include "resources/ResourceManager.hpp"
# include "ecs/components/Computer.hpp"
# include "scene/Scene.hpp"

# include "tinyxml2.h"
# include <json/json.hpp>

# include "ecs/factories/ComputerFactories.hpp"

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