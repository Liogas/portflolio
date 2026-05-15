#ifndef ANIMATIONSET_HPP
# define ANIMATIONSET_HPP

# include <iostream>
# include "Animation.hpp"
# include <unordered_map>

typedef struct	s_animationSet
{
	std::unordered_map<std::string, Animation>	animations;
}	AnimationSet;

#endif