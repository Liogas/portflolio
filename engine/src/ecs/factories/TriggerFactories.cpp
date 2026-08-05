#include "ecs/factories/TriggerFactories.hpp"

entt::entity	TriggerFactories::create(
	entt::registry &registry,
	std::string		&emit,
	std::string		&id,
	std::string		&animation,
	float			x,
	float			y,
	int				w,
	int				h,
	float			duration,
	bool			once
)
{
	auto entity = registry.create();
	registry.emplace<Position>(entity, x, y);
	registry.emplace<Collider>(entity, 0, 0, w, h);
	registry.emplace<Trigger>(entity, Trigger {
		.emit		= emit,
		.id			= id,
		.animation	= animation,
		.duration	= duration,
		.elapsed	= 0.f,
		.once		= once,
		.fired		= false,
		.active		= false
	});
	return (entity);
}
