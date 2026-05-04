#ifndef MOVEMENT_HPP
# define MOVEMENT_HPP

enum class EDirection {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    NONE
};

typedef	struct s_movement
{
	float		speed;
	EDirection	direction;
	EDirection	lastDirection;
	bool		isMoving;
}	Movement;

#endif