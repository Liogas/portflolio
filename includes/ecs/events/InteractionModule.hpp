#ifndef INTERACTIONMODULE_HPP
# define INTERACTIONMODULE_HPP

# include "ComputerInteractionSystem.hpp"
# include <iostream>

class InteractionModule
{
	public:
		InteractionModule(entt::registry &registry, entt::dispatcher &dispatcher);
	private:
		entt::registry				&_registry;
		entt::dispatcher			&_dispatcher;
		ComputerInteractionSystem	_computer;
};

#endif