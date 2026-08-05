#include "PylonFactories.hpp"

entt::entity	PylonFactories::create(
	entt::registry		&registry,
	const std::string 	&listen,
	float				x,
	float				y,
	int					w,
	int					h
)
{
	auto entity = registry.create();
	registry.emplace<Position>(entity, x, y);
	registry.emplace<Collider>(entity, 0, 0, w, h);
	registry.emplace<Pylon>(entity, Pylon { listen, false });
	return (entity);
}