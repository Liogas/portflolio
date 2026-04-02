#ifndef SPRITE_HPP
# define SPRITE_HPP

# include "RendererSDL.hpp"
# include "TextureSDL.hpp"

# include <memory>

typedef struct	paramAnimation
{
	std::string currName;
	std::string	prevAnim;
	float		speed;
	float		timer;
	int			maxFrame;
	int			currPos;
}	T_paramAnimation;

class Sprite
{
	public:
		Sprite(std::shared_ptr<TextureSDL> t, int w, int h, bool hasAnim);
		~Sprite();
		// SETTERS
		void	setDestPosition(int x, int y);
		void	setSrcPosition(int x, int y);
		void	setParamAnimation(T_paramAnimation &p);
		// GETTERS
		[[nodiscard]] std::shared_ptr<TextureSDL>		getTexture() const;
		[[nodiscard]] T_paramAnimation					&getParamAnimation();
		// METHODS
		void	render();
	private:
		std::shared_ptr<TextureSDL>	_texture;
		T_paramAnimation			_paramAnimation;
		SDL_Rect					_dest;
		SDL_Rect					_src;
		bool						_hasAnim;
};

#endif