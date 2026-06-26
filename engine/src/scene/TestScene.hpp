#ifndef TESTSCENE_HPP
# define TESTSCENE_HPP

# include "MapParser.hpp"
# include "TileMap.hpp"

# include "Scene.hpp"

# include <entt/entt.hpp>
# include <iostream>

class TestScene : public Scene
{
	public:
		TestScene(int width, int height);
		void load(World &world) override;
		void unload(World &world) override;
};

#endif