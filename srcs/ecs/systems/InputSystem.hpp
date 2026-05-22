#ifndef INPUTSYSTEM_HPP
# define INPUTSYSTEM_HPP

# include <entt/entt.hpp>

# include "Movement.hpp"
# include "PlayerTag.hpp"
# include "InputSDL.hpp"


void InputSystem(entt::registry &registry, const InputSDL &input);

#endif