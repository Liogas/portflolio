#ifndef COLLISIONSYSTEM_HPP
# define COLLISIONSYSTEM_HPP

# include "TileMap.hpp"

// COMPOSANTS ECS
# include "Movement.hpp"
# include "Position.hpp"
# include "Collider.hpp"


void	CollisionSystem(entt::registry &registry, TileMap &map, float dt);

#endif
