#ifndef SCENE_HPP
# define SCENE_HPP

# include <memory>

class TileMap;
class RendererSDL;
class SceneContext;

class Scene
{
	public:
		virtual 		~Scene() = default;
		// METHODS
		virtual void						load(SceneContext&) = 0;
		virtual void						unload(SceneContext&){}
		virtual void						onEnter(SceneContext&){}
		virtual void						onExit(SceneContext&){}
		virtual void						update(SceneContext&, float dt){}
		virtual void						render(SceneContext&, RendererSDL&){}

		// GETTERS
		[[nodiscard]] int	getHeight() const { return (this->_height); }
		[[nodiscard]] int	getWidth() const { return (this->_width); }
	protected:
		int 	_height;
		int		_width;
};

#endif