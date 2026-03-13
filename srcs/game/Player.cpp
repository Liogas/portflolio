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
	this->setupAnim();
	T_paramAnimation	p;
	p.currName = "standS";
	p.currPos = 0;
	p.prevAnim = "xxx";
	this->_sprite.setParamAnimation(p);
}

Player::~Player()
{
	std::cout << "Player destroyed" << std::endl;
}

void	Player::setupAnim()
{
	T_animation a;
	a.nbTiles = 6;
	a.posX = 0;
	a.posY = 4;
	a.sizeH = 64;
	a.sizeW = 64;
	this->_sprite.getTexture().addAnimation("walkS", a);
	a.posY = 5;
	this->_sprite.getTexture().addAnimation("walkN", a);
	a.posY = 6;
	this->_sprite.getTexture().addAnimation("walkE", a);
	a.posY = 7;
	this->_sprite.getTexture().addAnimation("walkW", a);
	a.posY = 0;
	a.nbTiles = 1;
	this->_sprite.getTexture().addAnimation("standS", a);
	a.posY = 1;
	a.nbTiles = 1;
	this->_sprite.getTexture().addAnimation("standN", a);
	a.posY = 2;
	a.nbTiles = 1;
	this->_sprite.getTexture().addAnimation("standE", a);
	a.posY = 3;
	a.nbTiles = 1;
	this->_sprite.getTexture().addAnimation("standW", a);

	// this->_sprite.getTexture().printAnimations();
}

// Plus tard prendre en compte une SCENE plutot que la fenetre
void	Player::move(EDirection dir, const Scene &scene)
{
	int	tmpX = this->_posX;
	int tmpY = this->_posY;
	T_paramAnimation &anim = this->_sprite.getParamAnimation();
	switch(dir)
	{
		case EDirection::LEFT :
			tmpX -= this->_speed;
			anim.prevAnim = anim.currName;
			anim.currName = "walkW";
			break;
		case EDirection::RIGHT :
			tmpX += this->_speed;
			anim.prevAnim = anim.currName;
			anim.currName = "walkE";
			break;
		case EDirection::BOTTOM :
			tmpY += this->_speed;
			anim.prevAnim = anim.currName;
			anim.currName = "walkS";
			break;
		case EDirection::TOP :
			tmpY -= this->_speed;
			anim.prevAnim = anim.currName;
			anim.currName = "walkN";
			break;
		case EDirection::NONE :
			this->choiceStandAnimation(anim);
			return ;
	}
	if (tmpX >= 0 && tmpX < scene.getWidth() - this->_sizeW
		&& tmpY >= 0 && tmpY < scene.getHeight() - this->_sizeH)
	{
		this->_posX = tmpX;
		this->_posY = tmpY;
	}
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

void	Player::update()
{
	T_paramAnimation &anim = this->_sprite.getParamAnimation();
	if (anim.currName == anim.prevAnim)
	{
		anim.currPos++;
		if (anim.currPos >= this->_sprite.getTexture().getAnimations().getAnimation(anim.currName)->nbTiles)
			anim.currPos = 0;
	} else
	{
		anim.currPos = 0;
	}
	this->_sprite.setSrcPosition(
		anim.currPos * 64,
		this->_sprite.getTexture().getAnimations().getAnimation(anim.currName)->posY * 64
	);
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