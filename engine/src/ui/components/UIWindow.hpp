#ifndef UIWINDOW_HPP
# define UIWINDOW_HPP

# include "RendererSDL.hpp"
# include "InputSDL.hpp"

class UIWindow
{
	public:
		virtual ~UIWindow() = default;
		virtual void	handleInput(const InputSDL &sdl)	= 0;
		virtual void	update(float dt) 					= 0;
		virtual void	render(RendererSDL &renderer) 		= 0;
		virtual bool	blocksGameplay() const				= 0;
		virtual bool	shouldClose() const					= 0;
};

#endif