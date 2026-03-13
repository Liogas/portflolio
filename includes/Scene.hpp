#ifndef SCENE_HPP
# define SCENE_HPP

# include "AppSDL.hpp"
# include "EventSDL.hpp"
# include "InputSDL.hpp"
# include "RendererSDL.hpp"
# include "GameState.hpp"

class GameState;

class Scene
{
	public:
		virtual 		~Scene() = default;
		// METHODS
		virtual void	onEnter() 													= 0;
		virtual void	onExit() 													= 0;
		virtual void	update(InputSDL &inputs, const GameState &gameState) 	= 0;
		virtual void	handleEvents(EventSDL &, const GameState &gameState)	= 0;
		virtual void	render(RendererSDL &, const GameState &gameState) 			= 0;
		[[nodiscard]] int	getHeight() const { return (this->_height); };
		[[nodiscard]] int	getWidth() const { return (this->_width); };
	protected:
		int _height;
		int	_width;
};

#endif