#ifndef TRIGGERSYSTEM_HPP
# define TRIGGERSYSTEM_HPP

# include <entt/entt.hpp>
# include <SDL2/SDL.h>

# include "ecs/components/Position.hpp"
# include "ecs/components/PlayerTag.hpp"
# include "ecs/components/Trigger.hpp"
# include "ecs/components/Collider.hpp"

void	TriggerSystem(
	entt::registry		&registry,
	entt::dispatcher	&dispatcher,
	float				dt
);

#endif