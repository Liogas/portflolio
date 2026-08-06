#include "PylonSystem.hpp"

void	PylonSystem(
	entt::registry	    &registry,
    TileMap             map,
	entt::dispatcher	&dispatcher,
    RendererSDL         &renderer,
	ResourceManager	    &rm,
	float				dt
)
{
    auto pylons = registry.view<Pylon>();
    for (auto entity : pylons)
    {
        auto &pylon  = pylons.get<Pylon>(entity);
        if (pylon.active)
            pylon.elapsed += dt;
        else
            pylon.elapsed = 0;
    }
}

void    onTriggerEntered(entt::registry &registry, const TriggerEnteredEvent &e)
{
	auto pylons = registry.view<Pylon>();
    int i = 1;
    float duration = e.duration / e.nbTarget;
	for (auto entity : pylons)
	{
        auto &pylon = pylons.get<Pylon>(entity);
		pylon.active = (!e.animation.empty() && pylon.listenEvent == e.animation);
        pylon.goal = duration * i;
        i++;
	}
}
