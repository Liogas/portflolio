#ifndef INPUTSYSTEM_HPP
# define INPUTSYSTEM_HPP

# include <entt/entt.hpp>

# include "ecs/components/Movement.hpp"
# include "ecs/components/PlayerTag.hpp"
# include "InputSDL.hpp"

# include "config/ControlsConfig.hpp"

# include "events/Events.hpp"


class World;

void InputSystem(
    entt::registry			&registry,
    entt::dispatcher        &dispatcher,
    const InputSDL  		&input,
    const ControlsConfig    &cfg
);

#endif