#ifndef SCENEMANAGER_HPP
# define SCENEMANAGER_HPP

# include "Scene.hpp"
# include "RessourceManager.hpp"

# include <memory>

class SceneManager
{
	public:
		SceneManager(RessourceManager &rm);
		~SceneManager(void);
		void	changeScene(std::unique_ptr<Scene> scene);
		// METHODS
		void	update(InputSDL &input, float deltaTime);
		void	render(RendererSDL &renderer);
		void	handleEvent(EventSDL &event);
	private:
		std::unique_ptr<Scene>	_currScene;
		RessourceManager		&_rm;
};

#endif