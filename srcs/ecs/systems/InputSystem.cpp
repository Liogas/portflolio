#include "InputSystem.hpp"

void InputSystem(entt::registry &registry, const InputSDL &input)
{
	auto view = registry.view<Movement, PlayerTag>();

	for (auto e : view)
	{
		auto &m = view.get<Movement>(e);
		m.direction = EDirection2::NONE;
		if (input.isKeyPressed(SDL_SCANCODE_A)) m.direction = EDirection2::LEFT;
		if (input.isKeyPressed(SDL_SCANCODE_D)) m.direction = EDirection2::RIGHT;
		if (input.isKeyPressed(SDL_SCANCODE_W)) m.direction = EDirection2::UP;
		if (input.isKeyPressed(SDL_SCANCODE_S)) m.direction = EDirection2::DOWN;
	}
}
