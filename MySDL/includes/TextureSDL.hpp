#ifndef TEXTURESDL_HPP
# define TEXTURESDL_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <stdexcept>

# include "RendererSDL.hpp"
# include "AnimationSDL.hpp"

class TextureSDL
{
	public:
		TextureSDL(RendererSDL &, const std::string &);
		~TextureSDL();
		// GETTERS
		SDL_Texture			*getTexture() const;
		const AnimationSDL	&getAnimations() const;
		
		void				getSize(int *w, int *h);
		// METHODS
		bool			render(SDL_Rect *src = nullptr, SDL_Rect *dst = nullptr);
		void			setAsTarget();
		void			resetTarget();
		void			printAnimations();
		void			addAnimation(std::string name, T_animation animation);
	private:
		SDL_Texture		*_texture;
		RendererSDL		&_renderer;
		AnimationSDL	_animations;
};

#endif