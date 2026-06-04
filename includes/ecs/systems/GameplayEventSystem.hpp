#ifndef GAMEPLAYEVENTSYSTEM_HPP
# define GAMEPLAYEVENTSYSTEM_HPP

# include <entt/entt.hpp>
# include "EventBus.hpp"
# include "Computer.hpp"
# include "World.hpp"

class World;

void	GameplayEventSystem(
    World           &world,
    entt::registry  &registry,
    EventBus        &bus,
    RendererSDL     &renderer
);

#endif