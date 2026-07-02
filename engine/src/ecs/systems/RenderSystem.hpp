#ifndef RENDERSYSTEM_HPP
# define RENDERSYSTEM_HPP

# include <entt/entt.hpp>

# include "graphics/Camera.hpp"

# include "ecs/components/Position.hpp"
# include "ecs/components/SpriteComponent.hpp"

void RenderSystem(entt::registry &registry, Camera &camera);

#endif