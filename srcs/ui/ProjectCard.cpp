#include "ProjectCard.hpp"

void	drawProjectCard(RendererSDL &renderer, const ProjectCard &card)
{
	SDL_RenderCopy(renderer.getRenderer(), card.titleText, nullptr, &card.titleRect);
}