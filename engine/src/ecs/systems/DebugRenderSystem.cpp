#include "DebugRenderSystem.hpp"
#include "utils/CollisionUtils.hpp"

static void	drawPolygon(
	SDL_Renderer	*r,
	const std::vector<SDL_Point> &points,
	Camera	&camera
)
{
	if (points.size() < 2)
		return ;
	for (size_t i = 0; i < points.size(); ++i)
	{
		SDL_Point a = points[i];
		SDL_Point b = points[(i + 1) % points.size()];
		SDL_RenderDrawLine(
			r,
			a.x - camera.getX(), a.y - camera.getY(),
			b.x - camera.getX(), b.y - camera.getY()
		);
	}
}

void    DebugRenderMapCollisions(
    TileMap &map,
    RendererSDL &renderer,
    Camera &camera
)
{
    SDL_Renderer *r = renderer.getRenderer();
    SDL_Rect visibleArea = {
        camera.getX(),
        camera.getY(),
        renderer.getWidth(),
        renderer.getHeight()
    };
    auto shapes = map.getWorldCollisionShapes(visibleArea);
    for (const auto &shape : shapes)
    {
        if (shape.type == CollisionShapeType::Rect)
        {

            SDL_SetRenderDrawColor(r, 255, 0, 0, 180);
            SDL_Rect screenRect = {
                shape.rect.x - camera.getX(),
                shape.rect.y - camera.getY(),
                shape.rect.w,
                shape.rect.h
            };
            SDL_RenderDrawRect(r, &screenRect);
        }
        else if (shape.convex)
        {
            SDL_SetRenderDrawColor(r, 255, 255, 0, 180);
            drawPolygon(r, shape.polygon, camera);
        }
        else
        {
            SDL_SetRenderDrawColor(r, 0, 255, 255, 180);
            for (const auto &tri : shape.triangles)
                drawPolygon(r, tri, camera);
            SDL_SetRenderDrawColor(r, 255, 165, 0, 180);
            drawPolygon(r, shape.polygon, camera);
        }
    }
}


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