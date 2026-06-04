#ifndef PROJECTCARD_HPP
# define PROJECTCARD_HPP

# include "RendererSDL.hpp"
# include "Project.hpp"

typedef struct s_projectCard
{
	SDL_Rect					rect;

	SDL_Texture					*titleText;
	SDL_Rect					titleRect;

	SDL_Texture					*descTex;
	SDL_Rect					descRect;
	
	std::vector<SDL_Texture*>	tagTex;
	std::vector<SDL_Rect>		tagRects;
}	ProjectCard;

void	drawProjectCard(RendererSDL &renderer, const ProjectCard &card);

# endif