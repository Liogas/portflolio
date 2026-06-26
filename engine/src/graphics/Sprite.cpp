#include "Sprite.hpp"

Sprite::Sprite(
	std::shared_ptr<TextureSDL> t,
	int	width,
	int	height,
	bool hasAnim
):
	_texture(t),
	_paramAnimation()
{
	this->_dest.h = height;
	this->_dest.w = width;
	this->_dest.x = 0;
	this->_dest.y = 0;
	
	this->_src.w = width;
	this->_src.h = height;
	this->_src.x = 0;
	this->_src.y = 0;

	this->_hasAnim = hasAnim;
	std::cout << "Sprite created" << std::endl;
}

Sprite::~Sprite()
{
	std::cout << "Sprite destroyed" << std::endl;
}

void	Sprite::setDestPosition(int x, int y)
{
	this->_dest.x = x;
	this->_dest.y = y;
}

void	Sprite::setSrcPosition(int x, int y)
{
	this->_src.x = x;
	this->_src.y = y;
}

void	Sprite::render()
{
	if (this->_hasAnim)
	{
		this->_src.x = this->_paramAnimation.currPos * this->_src.w;
		this->_src.y = this->_texture->getAnimations().getAnimation(this->_paramAnimation.currName)->posY * this->_src.h;
	}
	this->_texture->render(&this->_src, &this->_dest);
}

std::shared_ptr<TextureSDL>	Sprite::getTexture() const
{
	return (this->_texture);
}

void	Sprite::setParamAnimation(T_paramAnimation &param)
{
	this->_paramAnimation = param;
}

T_paramAnimation	&Sprite::getParamAnimation()
{
	return (this->_paramAnimation);
}