#ifndef COMPUTERFACTORIES_HPP
# define COMPUTERFACTORIES_HPP

# include <entt/entt.hpp>

// COMPONENTS
# include "Position.hpp"
# include "Collider.hpp"
# include "Interactable.hpp"

class ComputerFactories
{
	public:
		ComputerFactories() = 0;
		static entt::entity	create(
			entt::registry	&registry,
			int				x,
			int				y,
			int				w,
			int				h,
			std::string		&direction
		);
};

#endif