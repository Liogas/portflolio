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
		void	changeScene(std::unique_ptr<Scene> scene, World &world);
	private:
		std::unique_ptr<Scene>	_currScene;
		RessourceManager		&_rm;
};

#endif