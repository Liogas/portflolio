#ifndef PYLONFACTORIES_HPP
# define PYLONFACTORIES_HPP

# include <entt/entt.hpp>
# include "resources/ResourceManager.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/Position.hpp"
# include "ecs/components/Pylon.hpp"

class PylonFactories
{
	public:
		PylonFactories() = delete;
		static entt::entity	create(
			entt::registry		&registry,
			const std::string 	&listen,
			float				x,
			float				y,
			int					w,
			int					h
		);
};

#endif