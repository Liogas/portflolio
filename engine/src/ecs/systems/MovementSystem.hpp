#ifndef MOVEMENTSYSTEM_HPP
# define MOVEMENTSYSTEM_HPP

# include "ecs/components/Position.hpp"
# include "ecs/components/Movement.hpp"
# include "ecs/components/Velocity.hpp"
# include <entt/entt.hpp>

void	MovementSystem(entt::registry& registry);

#endif