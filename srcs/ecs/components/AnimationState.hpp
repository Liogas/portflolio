#ifndef ANIMATIONSTATE_HPP
# define ANIMATIONSTATE_HPP

# include <iostream>

typedef struct	s_animationState
{
	std::string	current;
	int			frame = 0;
	float		timer = 0.f
}	AnimationState;

#endif