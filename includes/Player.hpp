#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Sprite.hpp"
# include "WindowSDL.hpp"

enum class EDirection
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	NONE
};

class Player
{
	public:
		Player(TextureSDL &t, int w, int h);
		~Player();
		void	move(EDirection, WindowSDL &win);
		void	update();
		void	setupAnim();
		Sprite	&getSprite();
		void	render();
		void	choiceStandAnimation(T_paramAnimation &p);
	private:
		Sprite	_sprite;
		int		_posX;
		int		_posY;
		int		_speed;
		int		_sizeW;
		int		_sizeH;
};

#endif