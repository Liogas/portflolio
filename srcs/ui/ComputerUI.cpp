#include "ComputerUI.hpp"

void	drawComputerUI(const ComputerUI &computer, RendererSDL &renderer)
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
	drawTitleBar(renderer, computer.titleBar);
}
