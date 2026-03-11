#ifndef SCENE_HPP
# define SCENE_HPP

# include "AppSDL.hpp"
# include "WindowSDL.hpp"
# include "EventSDL.hpp"
# include "InputSDL.hpp"
# include "RendererSDL.hpp"

class Scene
{
	public:
		virtual ~Scene() = default;
		// METHODS
		virtual void handleEvents(EventSDL &) = 0;
		virtual void update(InputSDL &) = 0;
		virtual void render(RendererSDL &) = 0;
};

#endif