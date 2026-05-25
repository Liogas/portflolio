#ifndef DEBUGRENDERSYSTEM_HPP
# define DEBUGRENDERSYSTEM_HPP

# include <entt/entt.hpp>

# include "RendererSDL.hpp"
# include "DebugBox.hpp"
# include "Camera.hpp"

void	DebugRenderSystem(entt::registry &registry, RendererSDL &renderer, Camera &camera);

#endif