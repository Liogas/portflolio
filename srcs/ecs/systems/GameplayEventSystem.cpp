#include "GameplayEventSystem.hpp"

void	GameplayEventSystem(
	World 			&world,
	entt::registry 	&registry,
	EventBus 		&bus,
	RendererSDL		&renderer
)
{
	for (const auto &e : bus.events)
	{
		switch (e.type)
		{
			case Event::Type::Interact:
			{
				if (registry.all_of<Computer>(e.target))
				{
					world.getDispatcher().trigger(OpenComputerEvent{
						registry.get<Computer>(e.target).id
					});
				}
				break ;
			}
			default : std::cout << "WIP" << std::endl;
		}
	}
	bus.clear();
}