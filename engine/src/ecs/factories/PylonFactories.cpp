#include "PylonFactories.hpp"

entt::entity	PylonFactories::create(
	entt::registry		&registry,
	const std::string 	&listen,
	const std::string	&path,
	int					order,
	float				x,
	float				y,
	int					w,
	int					h,
	ResourceManager		&rm
)
{
	int size = 32;
	auto entity = registry.create();
	registry.emplace<Position>(entity, x, y);
	registry.emplace<Collider>(entity, 0, 0, w, h);
	SpriteComponent sprite;
	sprite.texture = rm.getTexture(path, TextureFolder::WORLD);
	sprite.width = size;
	sprite.height = size;
	sprite.src = { 256, 192, size, size };
	registry.emplace<SpriteComponent>(entity, sprite);
	registry.emplace<Pylon>(entity, Pylon { listen, false, order, 0.f, 0.f });
	return (entity);
}