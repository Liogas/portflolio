#ifndef INTERACTIONSYSTEM_HPP
# define INTERACTIONSYSTEM_HPP

# include <entt/entt.hpp>

# include "InputSDL.hpp"

# include "ecs/components/PlayerTag.hpp"
# include "ecs/components/Position.hpp"
# include "ecs/components/Movement.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/Interactable.hpp"
# include "ecs/components/DebugBox.hpp"

# include "events/Events.hpp"

void	InteractionSystem(
    entt::registry	    &registry,
    const InputSDL	    &input,
    entt::dispatcher    &dispatcher
);

#endif