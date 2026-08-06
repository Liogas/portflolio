#include "RenderSystem.hpp"

void	RenderSystem(entt::registry &registry, Camera &camera)
{
	auto view = registry.view<Position, SpriteComponent>();
	for (auto entity : view)
	{
		if (registry.all_of<Pylon>(entity))
		{
			auto &pylon = registry.get<Pylon>(entity);
			if (!pylon.active || pylon.elapsed < pylon.goal)
				continue ;
		}
		auto &pos = view.get<Position>(entity);
		auto &sprite = view.get<SpriteComponent>(entity);
		SDL_Rect dst = {
			static_cast<int>(pos.x) - camera.getX(),
			static_cast<int>(pos.y) - camera.getY(),
			sprite.width,
			sprite.height
		};
		sprite.texture->render(&sprite.src, &dst);
	}
}