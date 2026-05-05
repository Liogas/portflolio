#ifndef MOVEMENT_HPP
# define MOVEMENT_HPP

enum class EDirection2 {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};

typedef	struct s_movement
{
	float		speed;
	EDirection2	direction;
	EDirection2	lastDirection;
	bool		isMoving;
}	Movement;

#endif