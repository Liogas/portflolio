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
					std::cout << "Je rentre ici " << std::endl;
					auto &c = registry.get<Computer>(e.target);
					if (!c.poweredOn)
					{
						c.poweredOn = true;
						for (const auto &msg : c.messages)
							std::cout << msg << std::endl;
						world.gameState = GameState::ComputerInteraction;
					} else
					{
						c.poweredOn = false;
						world.gameState = GameState::Playing;
					}
				}
				break ;
			}
			default : std::cout << "WIP" << std::endl;
		}
	}
	bus.clear();
}