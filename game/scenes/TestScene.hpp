#ifndef TESTSCENE_HPP
# define TESTSCENE_HPP

# include "MapParser.hpp"
# include "map/TileMap.hpp"

# include "scene/Scene.hpp"

# include <entt/entt.hpp>
# include <iostream>

class TestScene : public Scene
{
	public:
		TestScene(int width, int height);
		void load(SceneContext &ctx) override;
		void unload(SceneContect &ctx) override;
};

#endif