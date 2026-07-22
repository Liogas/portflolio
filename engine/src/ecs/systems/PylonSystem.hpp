#ifndef PYLONSYSTEM_HPP
# define PYLONSYSTEM_HPP

# include <entt/entt.hpp>
# include "resources/ResourceManager.hpp"

# include "ecs/components/Position.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/SpriteComponent.hpp"


void	PylonSystem(
	entt::registry	&registry,
	entt::dispatcher	&dispatcher,
	RessourceManager	&rm,
	float				dt
);

#endif