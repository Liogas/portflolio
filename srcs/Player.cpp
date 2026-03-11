#include "Player.hpp"

Player::Player(TextureSDL &t, int w, int h):
	_sprite(t, w, h)
{
	std::cout << "Player created" << std::endl;
	this->_posX = 0;
	this->_posY = 0;
	this->_speed = 3;
	this->_sizeH = h;
	this->_sizeW = w;
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
}

// Plus tard prendre en compte une SCENE plutot que la fenetre
void	Player::move(EDirection dir, WindowSDL &win)
{
	int	tmpX = this->_posX;
	int tmpY = this->_posY;
	switch(dir)
	{
		case EDirection::LEFT :
			tmpX -= this->_speed;
			break;
		case EDirection::RIGHT :
			tmpX += this->_speed;
			break;
		case EDirection::BOTTOM :
			tmpY += this->_speed;
			break;
		case EDirection::TOP :
			tmpY -= this->_speed;
			break;
	}
	int	winWidth, winHeight;
	SDL_GetWindowSize(win.getWindow(), &winWidth, &winHeight);
	if (tmpX >= 0 && tmpX < winWidth - this->_sizeW
		&& tmpY >= 0 && tmpY < winHeight - this->_sizeH)
	{
		this->_posX = tmpX;
		this->_posY = tmpY;
	}
}

Sprite	&Player::getSprite()
{
	return (this->_sprite);
}

void	Player::render()
{
	this->_sprite.setDestPosition(this->_posX, this->_posY);
	this->_sprite.render();
}