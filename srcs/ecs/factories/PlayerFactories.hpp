#ifndef PLAYERFACTORIES_HPP
# define PLAYERFACTORIES_HPP

# include <entt/entt.hpp>

class PlayerFactories
{
	public:
		static entt::entity	create(
			entt::registry	&registry,
			float			x,
			float			y
		);
}

#endif