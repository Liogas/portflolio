#ifndef PYLONSYSTEM_HPP
# define PYLONSYSTEM_HPP

# include <entt/entt.hpp>

# include "map/TileMap.hpp"

# include "resources/ResourceManager.hpp"

# include "ecs/components/Position.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/SpriteComponent.hpp"
# include "ecs/components/Pylon.hpp"

# include "RendererSDL.hpp"

# include "events/Events.hpp"



void	PylonSystem(
	entt::registry	&registry,
	TileMap			map,
	entt::dispatcher	&dispatcher,
	RendererSDL			&renderer,
	ResourceManager		&rm,
	float				dt
);

void    onTriggerEntered(entt::registry &registry, const TriggerEnteredEvent &e);

#endif