#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Sprite.hpp"
# include "Scene.hpp"

enum class EDirection
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	NONE
};

class Scene;

class Player
{
	public:
		Player(TextureSDL &t, int w, int h);
		~Player();
		void					move(EDirection);
		void					update(float deltaTime, const Scene &scene);
		void					setupAnim();
		[[nodiscard]] Sprite	&getSprite();
		void					render();
		void					choiceStandAnimation(T_paramAnimation &p);
	private:
		Sprite		_sprite;
		int			_posX;
		int			_posY;
		int			_speed;
		int			_sizeW;
		int			_sizeH;
		EDirection	_direction;
		EDirection	_lastDirection;
		bool		_isMoving;
		void		updateAnimation(float deltaTime);
		std::string	getWalkAnim();
		std::string	getStandAnim();
};

#endif