#include "Computer.hpp"

Computer::Computer(int x, int y, int width, int height, std::string direction)
{
	this->_x = x;
	this->_y = y;
	this->_width = width;
	this->_height = height;
	this->_direction = direction;
	this->_on = false;
	std::cout << "Computer created" << std::endl;
}

Computer::~Computer()
{
	std::cout << "Computer destroyed" << std::endl;
}

bool	Computer::canInteract(const Player &player) const
{
	if (this->_direction == "bottom"
		&& player.getLastDirection() != EDirection::TOP)
		return (false);
	if (this->_direction == "top"
		&& player.getLastDirection() != EDirection::BOTTOM)
		return (false);
	if (this->_direction == "left"
		&& player.getLastDirection() != EDirection::RIGHT)
		return (false);
	if (this->_direction == "right"
		&& player.getLastDirection() != EDirection::LEFT)
		return (false);
	return (this->intersects(player.getInteractionBox()));
}

void	Computer::interact(const Entity &e)
{
	(void)e;
	if (this->_on)
		return ;
	this->_on = true;
}

void	Computer::update(float dt)
{
	(void)dt;
}

bool	Computer::isOn() const
{
	return (this->_on);
}