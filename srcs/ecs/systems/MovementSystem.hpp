#ifndef MOVEMENTSYSTEM_HPP
# define MOVEMENTSYSTEM_HPP

# include "Position.hpp"
# include "Movement.hpp"
# include <entt/entt.hpp>

void	MovementSystem(entt::registry& registry, float dt);

#endif