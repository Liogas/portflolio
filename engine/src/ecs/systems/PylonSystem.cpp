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
    std::cout << "================ PYLONSYSTEM ============" << std::endl;
    auto pylons = registry.view<Pylon, SpriteComponent>();
    for (auto entity : pylons)
    {
        std::cout << "DADSADWDWADWA" << std::endl;
        auto &pylon  = pylons.get<Pylon>(entity);
        auto &sprite = pylons.get<SpriteComponent>(entity);
        std::cout << "Pylon.active -> " << pylon.active << std::endl;
        if (pylon.active)
        {
            std::cout << "Je rentre ici" << std::endl;
            auto props = map.getTilesetByPath("/home/glions/portflolio/assets/tilesets/../textures/world/TX Props.png");
            int localId = 30;

            int col = localId % props->columns;
            int row = localId / props->columns;

            SDL_Rect src = {
                col * props->tileWidth,
                row * props->tileHeight,
                props->tileWidth,
                props->tileHeight
            };
            SDL_Rect dst = props->sprite->getDest();
            SDL_RenderCopy(
                renderer.getRenderer(),
                props->sprite->getTexture()->getTexture(),
                &src,
                &dst
            );
        }
        else
        {
            // Texture eteinte
        }
    }
}

void    onTriggerEntered(entt::registry &registry, const TriggerEnteredEvent &e)
{
	auto pylons = registry.view<Pylon>();
	for (auto entity : pylons)
	{
        auto &pylon = pylons.get<Pylon>(entity);
        std::cout << "listenEvent -> " << pylon.listenEvent << std::endl;
        std::cout << "animation -> " << e.animation << std::endl;
		pylon.active = (!e.animation.empty() && pylon.listenEvent == e.animation);
        std::cout << "active -> " << pylon.active << std::endl;
	}
}
