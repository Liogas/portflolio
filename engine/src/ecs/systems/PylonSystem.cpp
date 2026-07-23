#include "PylonSystem.hpp"

void	PylonSystem(
	entt::registry	&registry,
	entt::dispatcher	&dispatcher,
	RessourceManager	&rm,
	float				dt
)
{
    auto pylons = registry.view<Pylon, SpriteComponent>();
    for (auto entity : pylons)
    {
        auto &pylon  = pylons.get<Pylon>(entity);
        auto &sprite = pylons.get<SpriteComponent>(entity);

        if (pylon.active)
        {
            // Swap vers la texture allumee
            // ex: rm.getTexture("pylon_blue_on.png")
            // Tu adaptes selon comment tu gères tes sprites
        }
        else
        {
            // Texture eteinte
        }
    }
}

void    onTriggerEntered(entt::registry &registry, const TriggerEnteredEvent &e)
{
	auto pylons = registry.view<Pylon>;
	for (auto entity : pylons)
	{
		auto &pylon = pylons.get<Pylon>(entity);
		pylon.active = (pylon.listenEvent == e.animation && !e.animation.empty());
	}
}