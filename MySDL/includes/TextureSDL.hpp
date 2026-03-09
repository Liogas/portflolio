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
		void		getSize(int *w, int *h);
		bool		render(SDL_Rect *src = nullptr, SDL_Rect *dst = nullptr);
		void		setAsTarget();
		void		resetTarget();
	private:
		SDL_Texture	*_texture;
		RendererSDL	&_renderer;
};

#endif