#ifndef SCENECONTEXT_HPP
# define SCENECONTEXT_HPP

# include <entt/entt.hpp>

class ResourceManager;
class Camera;

struct SceneContext
{
	entt::registry				&registry;
	entt::dispatcher			&dispatcher;
	ResourceManager				&resources;
	Camera						&camera;
	std::unique_ptr<TileMap>	map;
};

#endif