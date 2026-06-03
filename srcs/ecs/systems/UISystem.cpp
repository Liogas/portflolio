#include "UISystem.hpp"

// static void drawProjectCard(
//     RendererSDL &renderer,
//     const ProjectCard &project,
//     int x,
//     int y
// )
// {
//     SDL_Renderer *r = renderer.getRenderer();
//     SDL_Rect card = {
//         x,
//         y,
//         220,
//         140
//     };
//     SDL_SetRenderDrawBlendMode(
//         r,
//         SDL_BLENDMODE_BLEND
//     );
//     SDL_SetRenderDrawColor(
//         r,
//         30,
//         30,
//         30,
//         240
//     );
//     SDL_RenderFillRect(
//         r,
//         &card
//     );
//     SDL_SetRenderDrawColor(
//         r,
//         255,
//         255,
//         255,
//         255
//     );
//     SDL_RenderDrawRect(
//         r,
//         &card
//     );
// }

// static void drawBkg(const ComputerData &data, RendererSDL &renderer)
// {
//     try
//     {
//         (void)data;
//         auto r = renderer.getRenderer();
//         SDL_Rect bkg = {
//             renderer.getWidth() / 4,
//             10,
//             renderer.getWidth() / 2,
//             renderer.getHeight() - 20
//         };
//         SDL_SetRenderDrawBlendMode(
//             r,
//             SDL_BLENDMODE_BLEND
//         );
//         // REMPLISSAGE
//         SDL_SetRenderDrawColor(
//             r,
//             30,
//             30,
//             30,
//             150
//         );
//         SDL_RenderFillRect(
//             r,
//             &bkg
//         );
//         // BORDURE
//         SDL_SetRenderDrawColor(
//             r,
//             255,
//             255,
//             255,
//             255
//         );
//         SDL_RenderDrawRect(
//             r,
//             &bkg
//         );
//     }
//     catch(const std::exception& e)
//     {
//         throw (std::runtime_error(e.what()));
//     }
    
// }

// void    drawProjectCard(
//     RendererSDL         &renderer, 
//     const ProjectCard   &c,
//     int                 x,
//     int                 y
// )
// {

// }

void drawTitle(
    RendererSDL& renderer,
    TTF_Font* font,
    const std::string& text,
    int x,
    int y
)
{
    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface* surface =
        TTF_RenderUTF8_Blended(
            font,
            text.c_str(),
            color
        );

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(
            renderer.getRenderer(),
            surface
        );

    SDL_Rect dst = {
        x,
        y,
        surface->w,
        surface->h
    };

    SDL_RenderCopy(
        renderer.getRenderer(),
        texture,
        nullptr,
        &dst
    );

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void    drawComputerUI(World &world, RendererSDL &renderer, const ComputerUI &ui)
{
	auto r = renderer.getRenderer();
    SDL_Rect bkg = {
        renderer.getWidth() / 4,
        10,
        renderer.getWidth() / 2,
        renderer.getHeight() - 20
    };
    SDL_SetRenderDrawColor(
        r,
        30,
        30,
        30,
        150
    );
    SDL_RenderFillRect(
        r,
        &bkg
    );
    // BORDURE
    SDL_SetRenderDrawColor(
        r,
        255,
        255,
        255,
        255
    );
    SDL_RenderDrawRect(
        r,
        &bkg
    );
    TTF_Font *font = world.getRm().getFont("WorkforceCombine_PERSONAL_USE_ONLY.otf", 36);
	if (!font)
		throw (std::runtime_error(TTF_GetError()));
    drawTitle(renderer, font, ui.title, 200, 100);
}


void	UISystem(World &world, RendererSDL &renderer)
{
	try
	{
		if (world.gameState != GameState::ComputerInteraction)
			return ;
        if (!world.getComputerUI().has_value())
            return ;
        drawComputerUI(world, renderer, *world.getComputerUI());
		// auto &r = world.getRegistry();
		// auto e = world.getActiveComputer();
		// if (e == entt::null || !r.valid(e))
		// 	return ;
		// auto &computer = r.get<Computer>(e);
		// auto &computerData = world.getCm().get(computer.id);
        // drawBkg(computerData, renderer);
		// int x = 50;
		// int y = 50;
		// for (auto &projectId : computerData.projectIds)
		// {
		// 	auto &project = world.getPm().get(projectId);
		// 	drawProjectCard(renderer, project, x, y);
		// 	x += 50;
		// 	y += 50;
		// }
	} catch (const std::exception &e)
	{
		std::cerr << "UISYSTEM" << std::endl;
		throw (std::runtime_error(e.what()));
	}
}
