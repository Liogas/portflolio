#ifndef PROJECTCARD_HPP
# define PROJECTCARD_HPP

# include "RendererSDL.hpp"

struct Project;

typedef struct s_projectCard
{
	const Project	*project;
	SDL_Rect		rect;
	bool			selected = false;
}	ProjectCard;

void	drawProjectCard(RendererSDL &renderer, const ProjectCard &card);

# endif