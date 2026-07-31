#include "CollisionSystem.hpp"

static bool	intersectPlayerVsShape(
	const SDL_Rect			&player,
	const CollisionShape	&shape
) 
{
	if (shape.type == CollisionShapeType::Rect)
		return (CollisionUtils::rectIntersect(player, shape.rect));
	auto playerPoly = CollisionUtils::rectToPolygon(player);
	if (shape.convex)
		return (CollisionUtils::satConvex(playerPoly, shape.polygon));
	for (const auto &tri : shape.triangles)
	{
		if (CollisionUtils::satConvex(playerPoly, tri))
			return (true);
	}
	return (false);
}

static bool	intersectCollision(
	const SDL_Rect	&player,
	const std::vector<CollisionShape> &shapes
)
{
	for (const auto &shape : shapes)
	{
		if (intersectPlayerVsShape(player, shape))
            return true;
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

		SDL_Rect futureX = {
			(int)(pos.x + vel.x * dt),
			(int)pos.y,
			col.width,
			col.height
		};
		auto shapesX = map.getWorldCollisionShapes(futureX);
		if (!intersectCollision(futureX, shapesX))
			pos.x += vel.x * dt;
		
		SDL_Rect futureY = {
			(int)pos.x,
			(int)(pos.y + vel.y * dt),
			col.width,
			col.height
		};
		auto shapesY = map.getWorldCollisionShapes(futureY);
		if (!intersectCollision(futureY, shapesY))
			pos.y += vel.y * dt;
		vel = {0.f, 0.f};
	}
}
