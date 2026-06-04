#ifndef ANIMATIONSET_HPP
# define ANIMATIONSET_HPP

# include <iostream>
# include <unordered_map>

typedef struct s_animation
{
	int		row;
	int		startFrame;
	int		frameCount;
	float	speed;
}	Animation;

typedef struct	s_animationSet
{
	std::unordered_map<std::string, Animation>	animations;
}	AnimationSet;

#endif