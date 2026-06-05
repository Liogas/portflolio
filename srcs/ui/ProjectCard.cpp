#include "ProjectCard.hpp"

void	drawProjectCard(RendererSDL &renderer, const ProjectCard &card)
{
	auto *r = renderer.getRenderer();
	UIStyle::applyColor(r, UIStyle::BorderColor);
	SDL_RenderDrawRect(r, &card.rect);
	SDL_RenderCopy(r, card.titleTex, nullptr, &card.titleRect);
	// SDL_RenderCopy(r, card.descTex, nullptr, &card.descRect);
	// for (size_t i = 0; i < card.tagTex.size(); i++)
    //     SDL_RenderCopy(r, card.tagTex[i], nullptr, &card.tagRects[i]);
}

void	destroyProjectCard(ProjectCard &c)
{
	SDL_DestroyTexture(c.titleTex);
}