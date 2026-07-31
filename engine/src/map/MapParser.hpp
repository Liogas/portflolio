#ifndef MapParser_HPP
# define MapParser_HPP

# include <iostream>
# include <filesystem>
# include <fstream>

# include <json/json.hpp>
# include "tinyxml2.h"

# include "map/TileMap.hpp"
# include "resources/ResourceManager.hpp"
# include "scene/Scene.hpp"

# include "ecs/components/Computer.hpp"

# include "ecs/factories/ComputerFactories.hpp"
# include "ecs/factories/PylonFactories.hpp" 
# include "ecs/factories/TriggerFactories.hpp"

# include "utils/CollisionUtils.hpp"

class MapParser
{
	public:
		MapParser() = delete;
		void	debugPrint() const;
		static std::unique_ptr<TileMap> start(
			const std::string 	&path,
			entt::registry 		&registry,
			ResourceManager		&rm
		);
};

#endif