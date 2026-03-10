#include "Player.hpp"

Player::Player(TextureSDL &t, int w, int h):
	_sprite(t, w, h)
{
	std::cout << "Player created with " << std::endl;
	this->_posX = 0;
	this->_posY = 0;
	this->_speed = 3;
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
}

void	Player::move(EDirection &dir)
{
	(void)dir;
}

Sprite	&Player::getSprite()
{
	return (this->_sprite);
}

void	Player::render()
{
	this->_sprite.render();
}