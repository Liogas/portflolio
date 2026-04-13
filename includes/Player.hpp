#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Sprite.hpp"
# include "Scene.hpp"
# include "Camera.hpp"

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
		Player(std::shared_ptr<TextureSDL> t, int w, int h);
		~Player();
		// METHODS
		void					move(EDirection);
		void					update(float deltaTime, const Scene &scene);
		void					setupAnim();
		void	 				render(Camera &camera);
		void					choiceStandAnimation(T_paramAnimation &p);
		// GETTERS
		[[nodiscard]] Sprite	&getSprite();
		[[nodiscard]] int		getX() const;
		[[nodiscard]] int		getY() const;
		// SETTERS
		void	setPos(int posX, int posY);
	private:
		// PROPS
		Sprite		_sprite;
		int			_posX;
		int			_posY;
		int			_speed;
		int			_sizeW;
		int			_sizeH;
		EDirection	_direction;
		EDirection	_lastDirection;
		bool		_isMoving;
		// METHODS
		void		updateAnimation(float deltaTime);
		std::string	getWalkAnim();
		std::string	getStandAnim();
};

#endif