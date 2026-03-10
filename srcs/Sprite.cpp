#include "Sprite.hpp"

Sprite::Sprite(
	TextureSDL &t,
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

void	Sprite::setSrcPosition(int x, int y)
{
	this->_src.x = x;
	this->_src.y = y;
}

void	Sprite::render()
{
	// std::cout << " SRC -> y:" << this->_src.y << " x:" << this->_src.x << " w:" << this->_src.w << " h:" << this->_src.h << std::endl;
	// std::cout << " dest -> y:" << this->_dest.y << " x:" << this->_dest.x << " w:" << this->_dest.w << " h:" << this->_dest.h << std::endl;
	this->_texture.render(&this->_src, &this->_dest);
}

TextureSDL	&Sprite::getTexture() const
{
	return (this->_texture);
}