#include "Player.hpp"

Player::Player(RendererSDL &r, std::string &p, int w, int h):
	_sprite(r , p, w, h)
{
	this->_posX = 0;
	this->_posY = 0;
}

Player::~Player()
{

}

void	Player::move(EDirection &dir)
{

}