#include "ecs/systems/AnimationStateSystem.hpp"

void	AnimationStateSystem(entt::registry &registry)
{
	auto view = registry.view<Movement, AnimationState>();
	for (auto e : view)
	{
		auto &mov = view.get<Movement>(e);
		auto &state = view.get<AnimationState>(e);

		if (mov.direction != mov.lastDirection)
		{
			state.frame = 0;
			state.timer = 0.f;
		}
		if (mov.isMoving)
		{
			switch (mov.direction)
			{
				case EDirection2::DOWN :
					state.current = "walk_down"; break ;
				case EDirection2::UP :
					state.current = "walk_up"; break ;
				case EDirection2::LEFT :
					state.current = "walk_left"; break ;
				case EDirection2::RIGHT :
					state.current = "walk_right"; break ;
				default: break ;
			}
		} else
		{
			switch (mov.lastDirection)
			{
				case EDirection2::DOWN :
					state.current = "idle_down"; break ;
				case EDirection2::UP :
					state.current = "idle_up"; break ;
				case EDirection2::LEFT :
					state.current = "idle_left"; break ;
				case EDirection2::RIGHT :
					state.current = "idle_right"; break ;
				default : break ;
			}
		}
	}
}