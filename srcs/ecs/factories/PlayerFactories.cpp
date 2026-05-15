#include "PlayerFactories.hpp"

static	entt::entity	PlayerFactories::create(
	entt::registry		&registry,
	RessourceManager	&rm,
	float				x,
	float				y,
	std::string			imgPath
)
{
	auto player = registry.create();
	registry.emplace<Position>(player, x, y);
	registry.emplace<Movement>(player, 5.f, EDirection2::NONE, EDirection2::NONE, false);
	registry.emplace<Velocity>(player, 0.f, 0.f);
	registry.emplace<Collider>(player, 64, 64);
	registry.emplace<PlayerTag>(player);
	registry.emplace<Persistent>(player);
	SpriteComponent sprite;
	sprite.texture = rm.getTexture(imgPath);
	sprite.width = 64;
	sprite.height = 64;
	sprite.src = { 0, 0, 64, 64 };
	registry.emplace<SpriteComponent>(player, sprite);
	AnimationSet set;
	set.animations["walk_down"] = { 0, 4, 6, 0.135f };
	set.animations["walk_up"] = { 0, 5, 6, 0.135f };
	set.animations["walk_right"] = { 0, 6, 6, 0.135f };
	set.animations["walk_left"] = { 0, 7, 6, 0.135f };
	set.animations["idle_down"] = { 0, 0, 1, 0.f };
	set.animations["idle_up"] = { 0, 1, 1, 0.f };
	set.animations["idle_right"] = { 0, 2, 1, 0.f };
	set.animations["idle_left"] = { 0, 3, 1, 0.f };
	registry.emplace<AnimationSet>(player, set);
	AnimationState	state;
	state.current = "idle_down";
	state.frame = 0;
	state.timer = 0.f;
	registry.emplace<AnimationState>(player, state);
	return (player);
}
