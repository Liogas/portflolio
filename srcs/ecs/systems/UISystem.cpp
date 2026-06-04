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
}
