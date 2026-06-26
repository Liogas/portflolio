#include "UIPanel.hpp"

void	UIPanel::draw(RendererSDL &renderer)
{
	auto *r = renderer.getRenderer();
	SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(
		r,
		this->background.r,
		this->background.g,
		this->background.b,
		this->background.a
	);
	SDL_RenderFillRect(r, &this->rect);
	SDL_SetRenderDrawColor(
		r,
		this->border.r,
		this->border.g,
		this->border.b,
		this->border.a
	);
	SDL_RenderDrawRect(r, &rect);
}