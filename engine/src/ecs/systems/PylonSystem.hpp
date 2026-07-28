#ifndef PYLONSYSTEM_HPP
# define PYLONSYSTEM_HPP

# include <entt/entt.hpp>
# include "resources/ResourceManager.hpp"

# include "ecs/components/Position.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/SpriteComponent.hpp"
# include "ecs/components/Pylon.hpp"

#include "events/Events.hpp"



void	PylonSystem(
	entt::registry	&registry,
	entt::dispatcher	&dispatcher,
	ResourceManager		&rm,
	float				dt
);

void    onTriggerEntered(entt::registry &registry, const TriggerEnteredEvent &e);

#endif