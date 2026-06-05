#ifndef PROJECTCARD_HPP
# define PROJECTCARD_HPP

# include "RendererSDL.hpp"
# include "Project.hpp"
# include "UIStyle.hpp"

typedef struct s_projectCard
{
	SDL_Rect					rect;

	SDL_Texture					*titleTex;
	SDL_Rect					titleRect;
	SDL_Point					titleSize;

	SDL_Texture					*descTex;
	SDL_Rect					descRect;
	SDL_Point					descSize;
	
	std::vector<SDL_Texture*>	tagTex;
	std::vector<SDL_Rect>		tagRects;
	std::vector<SDL_Point>		tagSizes;
}	ProjectCard;

void	drawProjectCard(RendererSDL &renderer, const ProjectCard &card);
void	destroyProjectCard(ProjectCard &p);

# endif