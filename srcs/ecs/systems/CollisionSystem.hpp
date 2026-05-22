#ifndef COLLISIONSYSTEM_HPP
# define COLLISIONSYSTEM_HPP

# include <entt/entt.hpp>

# include "TileMap.hpp"

// COMPOSANTS ECS
# include "Movement.hpp"
# include "Position.hpp"
# include "Collider.hpp"
# include "Velocity.hpp"


void	CollisionSystem(entt::registry &registry, TileMap &map, float dt);

#endif
