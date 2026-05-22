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
		if (map.isWalkable(futurX, pos.y, col.width, col.height))
    		pos.x = futurX;
		float futurY = pos.y + vel.y * dt;
		if (map.isWalkable(pos.x, futurY, col.width, col.height))
    		pos.y = futurY;

		// bool canMove = map.isWalkable(
		// 	futurX,
		// 	futurY,
		// 	col.width,
		// 	col.height
		// );

		// if (canMove)
		// {
		// 	pos.x = futurX;
		// 	pos.y = futurY;
		// }

		vel.x = 0.f;
		vel.y = 0.f;
	}
}
