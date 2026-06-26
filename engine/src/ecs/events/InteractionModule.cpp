#include "events/InteractionModule.hpp"

InteractionModule::InteractionModule(
	entt::registry 		&registry,
	entt::dispatcher	&dispatcher
):
	_registry(registry),
	_dispatcher(dispatcher),
	_computer(dispatcher, registry)
{
	std::cout << "InteractionModule created" << std::endl;
}

