#ifndef MOVEMENTSYSTEM_HPP
# define MOVEMENTSYSTEM_HPP

# include "Position.hpp"
# include "Movement.hpp"
# include "Velocity.hpp"
# include <entt/entt.hpp>
# include "World.hpp"

class World;

void	MovementSystem(World &world, entt::registry& registry);

#endif