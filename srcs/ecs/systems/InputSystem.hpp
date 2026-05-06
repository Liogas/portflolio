#ifndef INPUTSYSTEM_HPP
# define INPUTSYSTEM_HPP

# include <entt/entt.hpp>
# include "Movement.hpp"
# include "PlayerTag.hpp"

struct Input {
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};

void InputSystem(entt::registry &registry, const Input &input);

#endif