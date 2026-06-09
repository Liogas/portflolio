#ifndef COMPUTERUI_HPP
# define COMPUTERUI_HPP

# include "ProjectCard.hpp"
# include "Caroussel.hpp"

# include "UIStyle.hpp"

struct	ComputerUI
{
	UIText		title;
	Caroussel	caroussel;
	SDL_Rect	rect;
};

void	drawComputerUI(ComputerUI &computer, RendererSDL &renderer);
	
#endif