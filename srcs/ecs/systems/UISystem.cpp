#include "UISystem.hpp"

static void drawProjectCard(
    RendererSDL &renderer,
    const Project &project,
    int x,
    int y
)
{
	(void)project;
    SDL_Renderer *r = renderer.getRenderer();
    SDL_Rect card = {
        x,
        y,
        220,
        140
    };
    SDL_SetRenderDrawBlendMode(
        r,
        SDL_BLENDMODE_BLEND
    );
    SDL_SetRenderDrawColor(
        r,
        30,
        30,
        30,
        240
    );
    SDL_RenderFillRect(
        r,
        &card
    );
    SDL_SetRenderDrawColor(
        r,
        255,
        255,
        255,
        255
    );
    SDL_RenderDrawRect(
        r,
        &card
    );
}

void	UISystem(World &world, RendererSDL &renderer)
{
	try
	{
		if (world.gameState != GameState::ComputerInteraction)
			return ;
		auto &r = world.getRegistry();
		auto e = world.getActiveComputer();
		if (e == entt::null || !r.valid(e))
			return ;
		auto &computer = r.get<Computer>(e);
		auto &computerData = world.getCm().get(computer.id);
		int x = 50;
		int y = 50;
		for (auto &projectId : computerData.projectIds)
		{
			auto &project = world.getPm().get(projectId);
			drawProjectCard(renderer, project, x, y);
			x += 50;
			y += 50;
		}
	} catch (const std::exception &e)
	{
		std::cerr << "UISYSTEM" << std::endl;
		throw (std::runtime_error(e.what()));
	}
}
