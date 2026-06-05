#ifndef TITLEBAR_HPP
# define TITLEBAR_HPP

# include "RendererSDL.hpp"

struct	TitleBar
{
	SDL_Texture	*texture;
	SDL_Rect	rect;
	SDL_Rect	container;
};

void	drawTitleBar(
	RendererSDL		&renderer,
	const TitleBar	&titleBar
);

void	destroyTitleBar(TitleBar &t);

# endif