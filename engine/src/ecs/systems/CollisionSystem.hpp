#ifndef COLLISIONSYSTEM_HPP
# define COLLISIONSYSTEM_HPP

# include <entt/entt.hpp>

# include "map/TileMap.hpp"

// COMPOSANTS ECS
# include "ecs/components/Movement.hpp"
# include "ecs/components/Position.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/Velocity.hpp"

# include "utils/CollisionUtils.hpp"

void	CollisionSystem(entt::registry &registry, TileMap &map, float dt);

#endif