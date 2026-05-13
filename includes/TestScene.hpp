#ifndef TESTSCENE_HPP
# define TESTSCENE_HPP

# include "Position.hpp"
# include "Movement.hpp"
# include "PlayerTag.hpp"
# include "MapParseur.hpp"
# include "TileMap.hpp"
# include <entt/entt.hpp>
# include <iostream>

class TestScene : public Scene
{
	public:
		TestScene(int width, int height);
		void load(entt::registry &registry, RessourceManager &ressources) override;
		void unload(entt::registry &registry) override;
	private:
		std::unique_ptr<TileMap>	_map;
};

#endif