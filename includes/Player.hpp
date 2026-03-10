#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Sprite.hpp"

enum class EDirection
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

class Player
{
	public:
		Player(TextureSDL &t, int w, int h);
		~Player();
		void	move();
		Sprite	&getSprite();
		void	render();
	private:
		Sprite	_sprite;
		int		_posX;
		int		_posY;
		int		_speed;
};

#endif