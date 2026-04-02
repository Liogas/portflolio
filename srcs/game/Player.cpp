#include "Player.hpp"

Player::Player(std::shared_ptr<TextureSDL> t, int w, int h):
	_sprite(t, w, h, true)
{
	this->_posX 		= 0;
	this->_posY 		= 0;
	this->_speed 		= 2;
	this->_sizeH 		= h;
	this->_sizeW 		= w;
	this->_direction 	= EDirection::NONE;
	this->_lastDirection 	= EDirection::NONE;
	this->_isMoving 	= false;
	this->setupAnim();
	T_paramAnimation	p;
	p.currName	= "standS";
	p.prevAnim 	= "xxx";
	p.currPos	= 0;
	p.timer 	= 0.0f;
	this->_sprite.setParamAnimation(p);
	std::cout << "Player created" << std::endl;
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
}

void	Player::setupAnim()
{
	T_animation a;
	a.nbTiles 	= 6;
	a.posX 		= 0;
	a.posY 		= 4;
	a.sizeH 	= this->_sizeH;
	a.sizeW 	= this->_sizeW;
	a.speed 	= 0.135f;
	this->_sprite.getTexture()->addAnimation("walkS", a);
	a.posY 		= 5;
	this->_sprite.getTexture()->addAnimation("walkN", a);
	a.posY 		= 6;
	this->_sprite.getTexture()->addAnimation("walkE", a);
	a.posY 		= 7;
	this->_sprite.getTexture()->addAnimation("walkW", a);
	a.posY 		= 0;
	a.nbTiles 	= 1;
	a.speed 	= 0.0f;
	this->_sprite.getTexture()->addAnimation("standS", a);
	a.posY 		= 1;
	this->_sprite.getTexture()->addAnimation("standN", a);
	a.posY 		= 2;
	this->_sprite.getTexture()->addAnimation("standE", a);
	a.posY 		= 3;
	this->_sprite.getTexture()->addAnimation("standW", a);

	// this->_sprite.getTexture().printAnimations();
}

// Plus tard prendre en compte une SCENE plutot que la fenetre
void	Player::move(EDirection dir)
{
	if (dir == EDirection::NONE && this->_direction != EDirection::NONE)
		this->_lastDirection = this->_direction;
	this->_direction = dir;
	this->_isMoving = (dir != EDirection::NONE);
}

void	Player::choiceStandAnimation(T_paramAnimation &p)
{
	p.prevAnim = p.currName;
	if (p.currName[p.currName.length() - 1] == 'N')
		p.currName = "standN";
	else if (p.currName[p.currName.length() - 1] == 'S')
		p.currName = "standS";
	else if (p.currName[p.currName.length() - 1] == 'E')
		p.currName = "standE";
	else if (p.currName[p.currName.length() - 1] == 'W')
		p.currName = "standW";
}

void	Player::update(float deltaTime, const Scene &scene)
{
	int tmpX = this->_posX;
	int tmpY = this->_posY;

	if (this->_isMoving)
	{
		switch (this->_direction)
		{
			case EDirection::LEFT: tmpX -= this->_speed; break ;
			case EDirection::RIGHT: tmpX += this->_speed; break ;
			case EDirection::TOP: tmpY -= this->_speed; break ;
			case EDirection::BOTTOM: tmpY += this->_speed; break ;
			default: break;
		}
	}
	if (tmpX >= 0 && tmpX < scene.getWidth() - this->_sizeW &&
		tmpY >= 0 && tmpY < scene.getHeight() - this->_sizeH)
	{
		this->_posX = tmpX;
		this->_posY = tmpY;
	}
	this->updateAnimation(deltaTime);
}

void	Player::updateAnimation(float deltaTime)
{
	T_paramAnimation &anim = this->_sprite.getParamAnimation();
	if (this->_isMoving)
		anim.currName = getWalkAnim();
	else
		anim.currName = getStandAnim();
	anim.timer += deltaTime;
	const T_animation *animation = this->_sprite.getTexture()->getAnimations().getAnimation(anim.currName);
	if (anim.timer >= animation->speed)
	{
		anim.timer = 0;
		anim.currPos++;
		int max = animation->nbTiles;
		anim.currPos %= max;
	}
}

std::string	Player::getWalkAnim()
{
	switch (this->_direction)
	{
		case EDirection::LEFT: return "walkW";
		case EDirection::RIGHT: return "walkE";
		case EDirection::TOP: return "walkN";
		case EDirection::BOTTOM: return "walkS";
		default: return "standS";
	}
}

std::string	Player::getStandAnim()
{
	switch (this->_lastDirection)
	{
		case EDirection::LEFT: return "standW";
		case EDirection::RIGHT: return "standE";
		case EDirection::TOP: return "standN";
		case EDirection::BOTTOM: return "standS";
		default: return "standS";
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