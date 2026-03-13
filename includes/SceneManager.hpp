#ifndef SCENEMANAGER_HPP
# define SCENEMANAGER_HPP

# include "Scene.hpp"

# include <memory>

class SceneManager
{
	public:
		SceneManager(void);
		~SceneManager(void);
		void	changeScene(std::unique_ptr<Scene> scene);
		// METHODS
		void	update(InputSDL &input, const GameState &gameState);
		void	render(RendererSDL &renderer, const GameState &gameState);
		void	handleEvent(EventSDL &event, const GameState &gameState);
	private:
		std::unique_ptr<Scene>	_currScene;
};

#endif