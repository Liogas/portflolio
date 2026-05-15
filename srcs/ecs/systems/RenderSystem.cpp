#include "RenderSystem.hpp"

void	RenderSystem(entt::registry &registry, RendererSDL &renderer)
{
	auto view = registry.view<Position, SpriteComponent>();
	for (auto entity : view)
	{
		auto &pos = view.get<Position>(entity);
		auto &sprite = view.get<SpriteComponent>(entity);
		SDL_Rect dst = {
			(int)pos.x,
			(int)pos.y,
			sprite.width,
			sprite.height
		};
		sprite.texture->render(&sprite.src, &sprite.dst);
	}
}