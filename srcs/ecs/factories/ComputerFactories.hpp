#ifndef COMPUTERFACTORIES_HPP
# define COMPUTERFACTORIES_HPP

# include <entt/entt.hpp>

// COMPONENTS
# include "Position.hpp"
# include "Collider.hpp"
# include "Interactable.hpp"
# include "Computer.hpp"

class ComputerFactories
{
	public:
		ComputerFactories() = delete;
		static entt::entity	create(
			entt::registry		&registry,
			float				x,
			float				y,
			int					w,
			int					h,
			const std::string	&direction
		);
};

#endif