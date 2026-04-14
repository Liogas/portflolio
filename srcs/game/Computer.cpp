#include "Computer.hpp"

Computer::Computer(int x, int y, int width, int height)
{
	this->_x = x;
	this->_y = y;
	this->_width = width;
	this->_height = height;
	std::cout << "Computer created" << std::endl;
}

Computer::~Computer()
{
	std::cout << "Computer destroyed" << std::endl;
}

bool	Computer::canInteract(const Player &player) const
{
	return (this->intersects(player.getInteractionBox()));
}

void	Computer::interact(const Entity &e)
{
	(void)e;
	std::cout << "Interaction with computer" << std::endl;
}

void	Computer::update(float dt)
{
	(void)dt;
}