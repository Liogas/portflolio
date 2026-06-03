#ifndef COMPUTERUI_HPP
# define COMPUTERUI_HPP

# include "ProjectCard.hpp"
# include <vector>

struct	ComputerUI
{
	std::string 				title;
	SDL_Rect					windowRect;
	std::vector<ProjectCard>	cards;
	int							selectedCard;	
};
	
#endif