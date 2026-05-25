#include "PlayerFactories.hpp"

entt::entity	PlayerFactories::create(
	entt::registry		&registry,
	RessourceManager	&rm,
	float				x,
	float				y,
	const std::string	&imgPath
)
{
	int	size = 64;
	auto player = registry.create();
	registry.emplace<Position>(player, x, y);
	registry.emplace<Movement>(player, 200.f, EDirection2::NONE, EDirection2::NONE, false);
	registry.emplace<Velocity>(player, 0.f, 0.f);
	registry.emplace<Collider>(player, size, size);
	registry.emplace<PlayerTag>(player);
	registry.emplace<Persistent>(player);
	SpriteComponent sprite;
	sprite.texture = rm.getTexture(imgPath);
	sprite.width = size;
	sprite.height = size;
	sprite.src = { 0, 0, size, size };
	registry.emplace<SpriteComponent>(player, sprite);
	AnimationSet set;
	set.animations["walk_down"] = { 4, 0, 6, 0.135f };
	set.animations["walk_up"] = { 5, 0, 6, 0.135f };
	set.animations["walk_right"] = { 6, 0, 6, 0.135f };
	set.animations["walk_left"] = { 7, 0, 6, 0.135f };
	set.animations["idle_down"] = { 0, 0, 1, 0.f };
	set.animations["idle_up"] = { 1, 0, 1, 0.f };
	set.animations["idle_right"] = { 2, 0, 1, 0.f };
	set.animations["idle_left"] = { 3, 0, 1, 0.f };
	registry.emplace<AnimationSet>(player, set);
	AnimationState	state;
	state.current = "idle_down";
	state.frame = 0;
	state.timer = 0.f;
	registry.emplace<AnimationState>(player, state);
	return (player);
}
