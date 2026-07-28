#include "TriggerSystem.hpp"

void	TriggerSystem(
	entt::registry		&registry,
	entt::dispatcher	&dispatcher,
	float				dt
)
{
	auto players = registry.view<PlayerTag, Position, Collider>();
	auto triggers = registry.view<Trigger, Position, Collider>();

	for (auto trigEntity : triggers)
	{
		auto &trig = triggers.get<Trigger>(trigEntity);
		auto &tPos = triggers.get<Position>(trigEntity);
		auto &tCol = triggers.get<Collider>(trigEntity);

		if (trig.once && trig.fired)
			continue ;
		SDL_Rect trigBox = {
			(int)tPos.x, (int)tPos.y, tCol.width, tCol.height
		};
		bool playerInside = false;
		for (auto playerEntity : players)
		{
			auto &pPos = players.get<Position>(playerEntity);
			auto &pCol = players.get<Collider>(playerEntity);
			SDL_Rect	playerBox = {
				(int)pPos.x, (int)pPos.y, pCol.width, pCol.height
			};
			if (SDL_HasIntersection(&trigBox, &playerBox))
			{
				playerInside = true;
				break ;
			}
		}
		if (playerInside)
		{
			if (!trig.active)
			{
				trig.active = true;
				if (!trig.animation.empty())
					dispatcher.trigger(TriggerEnteredEvent{ trig.animation });
			}
			trig.elapsed += dt;
			if (trig.elapsed >= trig.duration)
			{
				dispatcher.trigger(TriggerFiredEvent{ trig.emit, trig.id });
				trig.fired = true;
				trig.elapsed = 0.f;
				trig.active = false;
			}
		}
		else
		{
			if (trig.active)
			{
				trig.active = false;
				trig.elapsed = 0.f;
				if (!trig.animation.empty())
					dispatcher.trigger(TriggerEnteredEvent{""});
			}
		}
	}
}