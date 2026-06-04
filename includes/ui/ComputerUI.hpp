#ifndef COMPUTERUI_HPP
# define COMPUTERUI_HPP

# include "ProjectCard.hpp"
# include "TitleBar.hpp"
# include "Caroussel.hpp"

# include "UIStyle.hpp"

struct	ComputerUI
{
	TitleBar	titleBar;
	Caroussel	caroussel;
	SDL_Rect	rect;			
};

void	drawComputerUI(const ComputerUI &computer, RendererSDL &renderer);
	
#endif