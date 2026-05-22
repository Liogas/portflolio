#include "CollisionSystem.hpp"

void	CollisionSystem(
	entt::registry	&registry,
	TileMap			&map,
	float			dt
)
{
	auto view = registry.view<Position, Velocity, Collider>();
	for (auto e : view)
	{
		auto &pos = view.get<Position>(e);
		auto &vel = view.get<Velocity>(e);
		auto &col = view.get<Collider>(e);

		float futurX = pos.x + vel.x * dt;
		float futurY = pos.y + vel.y * dt;

		bool canMove = map.isWalkable(
			futurX,
			futurY,
			col.width,
			col.height
		);

		if (canMove)
		{
			pos.x = futurX;
			pos.y = futurY;
		}

		vel.x = 0.f;
		vel.y = 0.f;
	}
}
