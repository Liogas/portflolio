#ifndef ANIMATION_HPP
# define ANIMATION_HPP

# include <iostream>

typedef struct s_animation
{
	std::string current;
	int			frame;
	float		timer;
}	Animation;

#endif