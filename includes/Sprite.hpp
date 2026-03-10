#ifndef SPRITE_HPP
# define SPRITE_HPP

# include "RendererSDL.hpp"
# include "TextureSDL.hpp"

class Sprite
{
	public:
		Sprite(TextureSDL &, int w, int h);
		~Sprite();
		void	setDestPosition(int x, int y);
		void	setSrcPosition(int x, int y);
		TextureSDL	&getTexture() const;
		void	render();
	private:
		TextureSDL	&_texture;
		SDL_Rect	_dest;
		SDL_Rect	_src;
};

#endif