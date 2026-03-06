#ifndef TEXTURESDL_HPP
# define TEXTURESDL_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <stdexcept>

# include "RendererSDL.hpp"

class TextureSDL
{
	public:
		TextureSDL(RendererSDL &, const std::string &);
		~TextureSDL();
		SDL_Texture	*getTexture() const;
		bool		render(SDL_Rect *src, SDL_Rect *dst);
	private:
		SDL_Texture	*_texture;
		RendererSDL	&_renderer;
};

#endif