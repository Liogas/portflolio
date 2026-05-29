#include "GameplayEventSystem.hpp"

void	GameplayEventSystem(World &world, entt::registry &registry, EventBus &bus)
{
	for (const auto &e : bus.events)
	{
		switch (e.type)
		{
			case Event::Type::Interact:
			{
				if (registry.all_of<Computer>(e.target))
				{
					auto &c = registry.get<Computer>(e.target);
					if (!c.poweredOn)
					{
						c.poweredOn = true;
						world.gameState = GameState::ComputerInteraction;
						world.setActiveComputer(e.target);
					} else
					{
						c.poweredOn = false;
						world.gameState = GameState::Playing;
						world.setActiveComputer(entt::null);
					}
				}
				break ;
			}
			default : std::cout << "WIP" << std::endl;
		}
	}
	bus.clear();
}