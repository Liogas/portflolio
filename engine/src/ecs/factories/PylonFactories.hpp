#ifndef PYLONFACTORIES_HPP
# define PYLONFACTORIES_HPP

# include <entt/entt.hpp>
# include "resources/ResourceManager.hpp"
# include "ecs/components/Collider.hpp"
# include "ecs/components/Position.hpp"
# include "ecs/components/Pylon.hpp"
# include "ecs/components/SpriteComponent.hpp"

class PylonFactories
{
	public:
		PylonFactories() = delete;
		static entt::entity	create(
			entt::registry		&registry,
			const std::string 	&listen,
			const std::string	&path,
			int					order,
			float				x,
			float				y,
			int					w,
			int					h,
			ResourceManager		&rm
		);
};

#endif