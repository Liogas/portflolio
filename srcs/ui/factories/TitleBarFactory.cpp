#include "TitleBarFactory.hpp"

/*
PENSER A CA
SDL_DestroyTexture(textTexture);
*/

TitleBar	TitleBarFactory::create(
	const std::string		&title,
	SDL_Rect				&container,
	RessourceManager		&rm,
	const RendererSDL		&renderer
)
{
	TitleBar bar;
	bar.container = {
		container.x,
		container.y,
		container.w,
		static_cast<int>(container.h * 0.2f)
	};
	UIStyle::Font font = UIStyle::Title;
	TTF_Font *ttf = rm.getFont(std::string(font.path), font.size);
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Surface *surface = TTF_RenderUTF8_Blended(ttf, title.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface);
	
	bar.texture = texture;
	bar.rect = {
		container.x + (container.w - surface->w) / 2,
		container.y + (bar.container.h - surface->h) / 2,
		surface->w,
		surface->h
	};
	SDL_FreeSurface(surface);
	return (bar);
}