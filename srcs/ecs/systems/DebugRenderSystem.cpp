#include "DebugRenderSystem.hpp"

void	DebugRenderSystem(entt::registry &registry, RendererSDL &renderer, Camera &camera)
{
	auto view = registry.view<DebugBox>();
	for (auto e : view)
	{
		auto &dbg = view.get<DebugBox>(e);
		SDL_SetRenderDrawColor(
			renderer.getRenderer(),
			dbg.color.r,
			dbg.color.g,
			dbg.color.b,
			dbg.color.a
		);
		dbg.box.x -= camera.getX();
		dbg.box.y -= camera.getY();
		SDL_RenderDrawRect(renderer.getRenderer(), &dbg.box);
	}

	auto d = registry.view<Collider, Position>();
	for (auto e : d)
	{
		auto &pos = d.get<Position>(e);
		auto &col = d.get<Collider>(e);

		SDL_Rect rect = {
			static_cast<int>(pos.x) - camera.getX(),
			static_cast<int>(pos.y) - camera.getY(),
			col.width,
			col.height
		};
		SDL_SetRenderDrawColor(
			renderer.getRenderer(),
			0,
			0,
			255,
			255
		);
		SDL_RenderDrawRect(renderer.getRenderer(), &rect);
	}
}