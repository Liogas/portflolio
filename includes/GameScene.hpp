#ifndef GAMESCENE_HPP
# define GAMESCENE_HPP

# include "Scene.hpp"

class GameScene : public Scene
{
	public:
		GameScene(void);
		~GameScene() override;
		void	onEnter() 							override;
		void	onExit() 							override;
		void	update(InputSDL &inputs, const GameState &gameState) 		override;
		void	handleEvents(EventSDL &event, const GameState &gameState) override;
		void	render(RendererSDL &, const GameState &gameState)	override;
};

#endif