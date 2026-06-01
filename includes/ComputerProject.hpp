#ifndef COMPUTERPROJECT_HPP
# define COMPUTERPROJECT_HPP

# include "ProjectCard.hpp"
# include <vector>

typedef struct	s_computerProject
{
	std::string					title;
	SDL_Rect					windowRect;
	std::vector<ProjectCard>	cards;
	ProjectCard					selectedCard;
}	ComputerProject;

#endif