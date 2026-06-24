#include "ComputerInteractionSystem.hpp"

ComputerInteractionSystem::ComputerInteractionSystem(
	entt::dispatcher	&dispatcher,
	entt::registry		&registry
):
	_dispatcher(dispatcher),
	_registry(registry)
{
	dispatcher.sink<InteractEvent>()
		.connect<&ComputerInteractionSystem::onInteract>(*this);
}

void	ComputerInteractionSystem::onInteract(const InteractEvent &e)
{
	if (!this->_registry.all_of<Computer>(e.target))
		return ;
	auto &comp = this->_registry.get<Computer>(e.target);
	this->_dispatcher.trigger(
		OpenComputerEvent{
			comp.id
		}
	);
}