#ifndef PLAYERFACTORIES_HPP
# define PLAYERFACTORIES_HPP

# include <entt/entt.hpp>

# include "resources/ResourceManager.hpp"

// COMPONENTS
# include "ecs/components/Persistent.hpp"
# include "ecs/components/Velocity.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/PlayerTag.hpp"
# include "ecs/components/Position.hpp"
# include "ecs/components/Movement.hpp"
# include "ecs/components/SpriteComponent.hpp"
# include "ecs/components/AnimationState.hpp"
# include "ecs/components/AnimationSet.hpp"

class PlayerFactories
{
	public:
		PlayerFactories() = delete;
		static entt::entity	create(
			entt::registry		&registry,
			ResourceManager	&rm,
			float				x,
			float				y,
			const std::string	&imgPath
		);
};

#endif