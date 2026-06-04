#ifndef CAROUSSEL_HPP
# define CAROUSSEL_HPP

# include "ProjectCard.hpp"
# include <vector>

struct	Caroussel
{
	std::vector<ProjectCard>	cards;
	int							selectedCard;
	SDL_Rect					rect;
	int							visibleCards;
	int							spacing;
};

void	layoutCaroussel(Caroussel &c);

# endif