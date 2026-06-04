#ifndef TITLEBAR_HPP
# define TITLEBAR_HPP

# include "RendererSDL.hpp"

/*
SDL_DestroyTexture(textTexture);
A PLACER QUELQUE PART
*/

struct	TitleBar
{
	SDL_Texture	*texture;
	SDL_Rect	rect;
	SDL_Rect	container;
};

// VOIR COMMENT AVOIR ACCES A FONTSMANAGER
void	drawTitleBar(
	RendererSDL		&renderer,
	const TitleBar	&titleBar
);

# endif