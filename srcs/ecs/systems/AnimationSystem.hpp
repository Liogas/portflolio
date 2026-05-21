#ifndef ANIMATIONSYSTEM_HPP
# define ANIMATIONSYSTEM_HPP

# include <entt/entt.hpp>

// COMPOSANTS ECS
# include "SpriteComponent.hpp"
# include "AnimationSet.hpp"
# include "AnimationState.hpp"

void	AnimationSystem(entt::registry &registry, float dt);

#endif