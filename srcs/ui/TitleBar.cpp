#include "TitleBar.hpp"

void	drawTitleBar(
	RendererSDL		&renderer,
	const TitleBar	&titleBar
)
{
	SDL_RenderCopy(
		renderer.getRenderer(),
		titleBar.texture,
		nullptr,
		&titleBar.rect
	);
}