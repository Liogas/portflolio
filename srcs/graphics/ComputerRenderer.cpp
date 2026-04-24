#include "ComputerRenderer.hpp"

ComputerRenderer::ComputerRenderer()
{
	std::cout << "ComputerRenderer created" << std::endl;
}

ComputerRenderer::~ComputerRenderer()
{
	std::cout << "ComputerRenderer deleted" << std::endl;
}

void	ComputerRenderer::draw(RendererSDL &renderer, const Computer &computer)
{
	(void)computer;
	int w, h;
	SDL_GetRendererOutputSize(renderer.getRenderer(), &w, &h);
	renderer.setDrawColor(255, 255, 255, 255);
	SDL_Rect rect;
	rect.w = w * 0.6;
	rect.h = h * 0.6;

	rect.x = (w - rect.w) / 2;
	rect.y = (h - rect.h) / 2;
	SDL_RenderFillRect(renderer.getRenderer(), &rect);
}