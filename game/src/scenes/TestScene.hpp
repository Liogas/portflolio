#ifndef TESTSCENE_HPP
# define TESTSCENE_HPP

# include "map/MapParser.hpp"
# include "map/TileMap.hpp"

# include "scene/Scene.hpp"
# include "scene/SceneContext.hpp"

# include <entt/entt.hpp>
# include <iostream>

class TestScene : public Scene
{
	public:
		TestScene(int width, int height);
		void load(SceneContext &ctx) override;
		void unload(SceneContext &ctx) override;
};

#endif