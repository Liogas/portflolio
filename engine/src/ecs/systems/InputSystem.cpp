#include "InputSystem.hpp"

static void	inputPlaying(
	entt::registry			&registry,
	entt::dispatcher		&dispatcher,
	const InputSDL 			&input,
	const ControlsConfig	&cfg
)
{
	auto view = registry.view<Movement, PlayerTag>();

	for (auto e : view)
	{
		auto &m = view.get<Movement>(e);
		m.direction = EDirection2::NONE;
		if      (input.isKeyDown(cfg.get(Action::MoveLeft)))  m.direction = EDirection2::LEFT;
        else if (input.isKeyDown(cfg.get(Action::MoveRight))) m.direction = EDirection2::RIGHT;
        else if (input.isKeyDown(cfg.get(Action::MoveUp)))    m.direction = EDirection2::UP;
        else if (input.isKeyDown(cfg.get(Action::MoveDown)))  m.direction = EDirection2::DOWN;
		else if (input.isKeyPressed(cfg.get(Action::Pause)))
            dispatcher.trigger(OpenPauseMenuEvent{});
		if (m.direction != EDirection2::NONE)
			m.lastDirection = m.direction;
	}
}

void InputSystem(
    entt::registry			&registry,
	entt::dispatcher		&dispatcher,
    const InputSDL  		&input,
    const ControlsConfig    &cfg
)
{
	inputPlaying(registry, dispatcher, input, cfg);
}
