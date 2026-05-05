#include "InputSystem.hpp"

void InputSystem(entt::registry &registry, const Input &input)
{
	auto view = registry.view<Movement, PlayerTag>();

	for (auto e : view)
	{
		auto &m = view.get<Movement>(e);
		m.direction = EDirection2::NONE;
		if (input.left) m.direction = EDirection2::LEFT;
		if (input.right) m.direction = EDirection2::RIGHT;
		if (input.up) m.direction = EDirection2::UP;
		if (input.down) m.direction = EDirection2::DOWN;
	}
}
