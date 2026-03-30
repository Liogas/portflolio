#ifndef GAMESCENE_HPP
# define GAMESCENE_HPP

# include "Scene.hpp"
# include "TileMap.hpp"
# include "MapParseur.hpp"

class GameScene : public Scene
{
	public:
		GameScene(int width, int height);
		~GameScene() override;
		void	onEnter() 							override;
		void	onExit() 							override;
		void	update(InputSDL &inputs, const GameState &gameState, float deltaTime) override;
		void	handleEvents(EventSDL &event, const GameState &gameState) override;
		void	render(RendererSDL &, const GameState &gameState) override;
	private:
		TileMap	*_map;
};

#endif