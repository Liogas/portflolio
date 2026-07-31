#ifndef DEBUGRENDERSYSTEM_HPP
# define DEBUGRENDERSYSTEM_HPP

# include <entt/entt.hpp>

# include "RendererSDL.hpp"

# include "ecs/components/DebugBox.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/Position.hpp"

# include "graphics/Camera.hpp"
# include "map/TileMap.hpp"

void	DebugRenderSystem(
    entt::registry &registry,
    RendererSDL &renderer,
    Camera &camera
);
void    DebugRenderMapCollisions(
    TileMap &map,
    RendererSDL &renderer,
    Camera &camera
);

#endif