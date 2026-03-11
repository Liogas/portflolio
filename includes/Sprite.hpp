#ifndef SPRITE_HPP
# define SPRITE_HPP

# include "RendererSDL.hpp"
# include "TextureSDL.hpp"

typedef struct	paramAnimation
{
	std::string currName;
	std::string	prevAnim;
	int			 currPos;
}	T_paramAnimation;

class Sprite
{
	public:
		Sprite(TextureSDL &, int w, int h);
		~Sprite();
		// SETTERS
		void	setDestPosition(int x, int y);
		void	setSrcPosition(int x, int y);
		void	setParamAnimation(T_paramAnimation &p);
		// GETTERS
		TextureSDL				&getTexture() const;
		T_paramAnimation		&getParamAnimation();
		// METHODS
		void	render();
	private:
		TextureSDL			&_texture;
		T_paramAnimation	_paramAnimation;
		SDL_Rect			_dest;
		SDL_Rect			_src;
};

#endif