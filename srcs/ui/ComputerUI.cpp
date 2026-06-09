#include "ComputerUI.hpp"

void	drawComputerUI(ComputerUI &computer, RendererSDL &renderer)
{
	auto r = renderer.getRenderer();
	SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
	UIStyle::applyColor(r, UIStyle::BackgroundColor);
    SDL_RenderFillRect(
        r,
        &computer.rect
    );
	UIStyle::applyColor(r, UIStyle::BorderColor);
    SDL_RenderDrawRect(
        r,
        &computer.rect
    );
	computer.title.draw(renderer);
    drawCaroussel(renderer, computer.caroussel);
}
