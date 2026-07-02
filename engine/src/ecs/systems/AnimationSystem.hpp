#ifndef ANIMATIONSYSTEM_HPP
# define ANIMATIONSYSTEM_HPP

# include <entt/entt.hpp>

// COMPOSANTS ECS
# include "ecs/components/SpriteComponent.hpp"
# include "ecs/components/AnimationSet.hpp"
# include "ecs/components/AnimationState.hpp"

void	AnimationSystem(entt::registry &registry, float dt);

#endif