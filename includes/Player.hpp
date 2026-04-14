#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Sprite.hpp"
# include "Entity.hpp"

# include <functional>

enum class EDirection
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	NONE
};

class Entity;

class Player : public Entity
{
	public:
		Player(std::shared_ptr<TextureSDL> t, int w, int h);
		~Player() override;
		// METHODS
		void					move(EDirection);
		void					update(float deltaTime) override;
		void					interact(const Entity &e) override;
		void					setupAnim();
		void	 				render(Camera &camera);
		void					choiceStandAnimation(T_paramAnimation &p);
		void					updateWithCollision(
									std::function<bool(int, int)> isWalkable,
									int sceneWidth,
									int sceneHeight
								);
		// GETTERS
		[[nodiscard]] Sprite	&getSprite();
		[[nodiscard]] t_rect	getInteractionBox() const;
	private:
		// PROPS
		Sprite		_sprite;
		int			_speed;
		EDirection	_direction;
		EDirection	_lastDirection;
		bool		_isMoving;
		// METHODS
		void		updateAnimation(float deltaTime);
		std::string	getWalkAnim();
		std::string	getStandAnim();
};

#endif