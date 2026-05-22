#ifndef PLAYERFACTORIES_HPP
# define PLAYERFACTORIES_HPP

# include <entt/entt.hpp>

# include "RessourceManager.hpp"

// COMPONENTS
# include "Persistent.hpp"
# include "Velocity.hpp"
# include "Collider.hpp"
# include "PlayerTag.hpp"
# include "Position.hpp"
# include "Movement.hpp"
# include "SpriteComponent.hpp"
# include "AnimationState.hpp"
# include "AnimationSet.hpp"

class PlayerFactories
{
	public:
		PlayerFactories() = delete;
		static entt::entity	create(
			entt::registry		&registry,
			RessourceManager	&rm,
			float				x,
			float				y,
			const std::string	&imgPath
		);
};

#endif