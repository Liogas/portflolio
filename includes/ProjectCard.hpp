#ifndef PROJECTCARD_HPP
# define PROJECTCARD_HPP

# include "RendererSDL.hpp"
# include "Project.hpp"

typedef struct s_projectCard
{
	const Project	*project;
	SDL_Rect		rect;
	bool			selected;
}	ProjectCard;

void	drawProjectCard(RendererSDL &renderer, const ProjectCard &card);

# endif