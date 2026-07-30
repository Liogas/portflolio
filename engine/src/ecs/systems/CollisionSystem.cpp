#include "CollisionSystem.hpp"

static bool	intersectCollision(
	const SDL_Rect	&player,
	const std::vector<CollisionShape> &shapes
)
{
	for (const auto &shape : shapes)
	{
		if (shape.type == CollisionShapeType::Rect)
		{
			if (SDL_HasIntersection(&player, &shape.rect))
				return (true);
		}
	}
	return (false);
}

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

		SDL_Rect player = {
			(int)(pos.x + vel.x * dt),
			(int)pos.y,
			col.width,
			col.height
		};

		auto shapes = map.getWorldCollisionShapes(player);
		if (!intersectCollision(player, shapes))
			pos.x += vel.x * dt;
		
		player = 
		{
			(int)pos.x,
			(int)(pos.y + vel.y * dt),
			col.width,
			col.height
		};

		shapes = map.getWorldCollisionShapes(player);
		if (!intersectCollision(player, shapes))
			pos.y += vel.y * dt;
		vel = {0.f, 0.f};
	}
}
