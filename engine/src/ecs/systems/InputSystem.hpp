#ifndef INPUTSYSTEM_HPP
# define INPUTSYSTEM_HPP

# include <entt/entt.hpp>

# include "Movement.hpp"
# include "PlayerTag.hpp"
# include "InputSDL.hpp"

# include "ControlsConfig.hpp"

# include "World.hpp"

class World;

void InputSystem(
    World &world,
    entt::registry			&registry,
    const InputSDL  		&input,
    const ControlsConfig    &cfg
);

#endif