#ifndef SPRITE_HPP
# define SPRITE_HPP

# include "RendererSDL.hpp"
# include "TextureSDL.hpp"

class Sprite
{
	public:
		Sprite(TextureSDL &, int w, int h);
		void	setDestPosition(int x, int y);
		void	render();
	private:
		TextureSDL	&_texture;
		SDL_Rect	_dest;
		SDL_Rect	_src;
};

#endif