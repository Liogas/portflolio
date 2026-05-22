#ifndef RENDERSYSTEM_HPP
# define RENDERSYSTEM_HPP

# include <entt/entt.hpp>

# include "Camera.hpp"

# include "Position.hpp"
# include "SpriteComponent.hpp"

void RenderSystem(entt::registry &registry, Camera &camera);

#endif