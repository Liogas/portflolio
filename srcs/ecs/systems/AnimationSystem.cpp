#include "AnimationSystem.hpp"

void	AnimationSystem(entt::registry &registry, float dt)
{
	auto view = registry.view<
		SpriteComponent,
		AnimationSet,
		AnimationState 
	>();

	for (auto e : view)
	{
		auto &sprite = view.get<SpriteComponent>(e);
		auto &state = view.get<AnimationState>(e);
		auto &set = view.get<AnimationSet>(e);

		auto it = set.animations.find(state.current);
		if (it == set.animations.end())
			continue ;
		const Animation &anim = it->second;

		state.timer += dt;

		if (anim.speed > 0.f && state.timer >= anim.speed)
		{
			state.timer = 0.f;
			state.frame++;
			state.frame %= anim.frameCount;
		}

		sprite.src.x = (anim.startFrame + state.frame) * sprite.width;
		sprite.src.y = anim.row * sprite.height;
		sprite.src.w = sprite.width;
		sprite.src.h = sprite.height;
	}
}