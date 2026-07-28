#ifndef IGAME_HPP
# define IGAME_HPP

#include <entt/entt.hpp>

# include "InputSDL.hpp"
# include "RendererSDL.hpp"

class IGame
{
	public:
		virtual ~IGame() = default;
		virtual void	init(RendererSDL &, entt::registry &) = 0;
		virtual void	update(RendererSDL &, InputSDL &, float dt) = 0;
		virtual void	render(RendererSDL &) = 0;
		virtual bool	isRunning() const = 0;
};

#endif