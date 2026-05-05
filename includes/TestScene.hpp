#ifndef TESTSCENE_HPP
# define TESTSCENE_HPP

# include "Position.hpp"
# include "Movement.hpp"
# include "PlayerTag.hpp"
# include <entt/entt.hpp>
# include <iostream>

class TestScene
{
	public:
		TestScene();
		void load(entt::registry &registry);
};

#endif