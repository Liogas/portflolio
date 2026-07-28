#ifndef TRIGGERFACTORIES_HPP
# define TRIGGERFACTORIES_HPP

# include <entt/entt.hpp>

# include "ecs/components/Position.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/Trigger.hpp"

class TriggerFactories
{
	public:
		TriggerFactories() = delete;
		static entt::entity	create(
			entt::registry &registry,
			std::string		&emit,
			std::string		&id,
			std::string		&animation,
			float			x,
			float			y,
			int				w,
			int				h,
			float			duration,
			bool			once
		);
};

#endif