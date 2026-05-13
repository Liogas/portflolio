#include "PlayerFactories.hpp"

static	entt::entity	PlayerFactories::create(
	entt::registry	&registry,
	float			x,
	float			y
)
{
	auto player = registry.create();
	registry.emplace<Position>(player, x, y);
	registry.emplace<Movement>(player, 5.f, EDirection2::NONE, EDirection2::NONE, false);
	registry.emplace<Velocity>(player, 0.f, 0.f);
	registry.emplace<Collider>(player, 64, 64);
	registry.emplace<PlayerTag>(player);
	registry.emplace<Persistent>(player);
	return (player);
}