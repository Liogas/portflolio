#include "Sprite.hpp"

Sprite::Sprite(
	TextureSDL &t
	int	width,
	int	height
):
	_texture(t)
{
	this->_dest.h = height;
	this->_dest.w = width;
	this->_dest.x = 0;
	this->_dest.y = 0;
	
	this->_src.w = width;
	this->_src.h = height;
	this->_src.x = 0;
	this->_src.y = 0;
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

void	Sprite::render()
{
	this->_texture.render(&this->_src, &this->_dest);
}