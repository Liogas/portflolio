#include "UISystem.hpp"

void	UISystem(World &world, RendererSDL &renderer)
{
	try
	{
		if (world.gameState != GameState::ComputerInteraction)
			return ;
        if (!world.getComputerUI().has_value())
            return ;
        drawComputerUI(*world.getComputerUI(), renderer);
	} catch (const std::exception &e)
	{
		std::cerr << "UISYSTEM" << std::endl;
		throw (std::runtime_error(e.what()));
	}
	double step = 0.01;
	double t;

	int prev_x = -1;
	int prev_y = -1;

	for (t = 0; t <= 2 * M_PI; t += step)
	{
    	int x = 400 + cos(t) * 100;
    	int y = 300 + sin(t) * 50;

    	if (prev_x != -1)
        	SDL_RenderDrawLine(renderer.getRenderer(), prev_x, prev_y, x, y);

    	prev_x = x;
    	prev_y = y;
	}
}
