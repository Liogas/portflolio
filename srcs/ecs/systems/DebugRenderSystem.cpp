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

		SDL_RenderDrawRect(renderer.getRenderer(), &dbg.box);
	}
}