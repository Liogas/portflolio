#include "InputSystem.hpp"

void InputSystem(entt::registry &registry, const InputSDL &input)
{
	auto view = registry.view<Movement, PlayerTag>();

	for (auto e : view)
	{
		auto &m = view.get<Movement>(e);
		m.direction = EDirection2::NONE;
		if (input.isKeyPressed(SDL_SCANCODE_A)) m.direction = EDirection2::LEFT;
		else if (input.isKeyPressed(SDL_SCANCODE_D)) m.direction = EDirection2::RIGHT;
		else if (input.isKeyPressed(SDL_SCANCODE_W)) m.direction = EDirection2::UP;
		else if (input.isKeyPressed(SDL_SCANCODE_S)) m.direction = EDirection2::DOWN;
		if (m.direction != EDirection2::NONE)
			m.lastDirection = m.direction;
	}
}
