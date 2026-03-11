#include "AnimationSDL.hpp"

AnimationSDL::AnimationSDL(void):
	_animations()
{
	std::cout << "AnimationSDL created" << std::endl;
}

AnimationSDL::~AnimationSDL()
{
	std::cout << "AnimationSDL destroyed" << std::endl;
}

void	AnimationSDL::addAnimation(std::string name, T_animation anim)
{
	if (!this->_animations.contains(name))
	{
		anim.name = name;
		this->_animations[name] = anim;
		std::cout << "Animation " << name << " added" << std::endl;		
	}
	else
		std::cout << "Animation " << name << " already exists" << std::endl;		
}

void	AnimationSDL::print()
{
	for (auto a : this->_animations)
	{
		std::cout << "Animation " << a.second.name << std::endl;
		std::cout << "Nb tiles : " << a.second.nbTiles << std::endl;
		std::cout << "posX : " << a.second.posX << " ; poY : " << a.second.posY << std::endl;
		std::cout << "sizeH : " << a.second.sizeH << " ; sizeW : " << a.second.sizeW << std::endl;
	}
}

const T_animation	*AnimationSDL::getAnimation(std::string name) const
{
	if (this->_animations.contains(name))
		return (&this->_animations.at(name));
	return (nullptr);
}
