#ifndef COMPUTERFACTORIES_HPP
# define COMPUTERFACTORIES_HPP

# include <entt/entt.hpp>

// COMPONENTS
# include "ecs/components/Position.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/Interactable.hpp"
# include "ecs/components/Computer.hpp"

class ComputerFactories
{
	public:
		ComputerFactories() = delete;
		static entt::entity	create(
			entt::registry		&registry,
			const std::string	&id,
			float				x,
			float				y,
			int					w,
			int					h,
			const std::string	&direction
		);
};

#endif