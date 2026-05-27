#include "InputSystem.hpp"

void InputSystem(World &world, entt::registry &registry, const InputSDL &input)
{
	auto view = registry.view<Movement, PlayerTag>();

	if (input.isKeyPressed(SDL_SCANCODE_F3))
		world.toggleDebug();

	if (world.gameState != GameState::Playing)
		return ;

	for (auto e : view)
	{
		auto &m = view.get<Movement>(e);
		m.direction = EDirection2::NONE;
		if (input.isKeyDown(SDL_SCANCODE_A)) m.direction = EDirection2::LEFT;
		else if (input.isKeyDown(SDL_SCANCODE_D)) m.direction = EDirection2::RIGHT;
		else if (input.isKeyDown(SDL_SCANCODE_W)) m.direction = EDirection2::UP;
		else if (input.isKeyDown(SDL_SCANCODE_S)) m.direction = EDirection2::DOWN;
		if (m.direction != EDirection2::NONE)
			m.lastDirection = m.direction;
	}
}
