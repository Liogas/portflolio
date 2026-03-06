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
		Player(RendererSDL &, std::string &, int w, int h);
		~Player();
		void	move(EDirection &);
	private:
		Sprite	_sprite;
		int		_posX;
		int		_posY;
};

#endif