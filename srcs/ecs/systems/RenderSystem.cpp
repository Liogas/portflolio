#include "RenderSystem.hpp"

void	RenderSystem(entt::registry &registry)
{
	auto view = registry.view<Position, SpriteComponent>();
	for (auto entity : view)
	{
		auto &pos = view.get<Position>(entity);
		auto &sprite = view.get<SpriteComponent>(entity);
		SDL_Rect dst = {
			static_cast<int>(pos.x),
			static_cast<int>(pos.y),
			sprite.width,
			sprite.height
		};
		sprite.texture->render(&sprite.src, &dst);
	}
}