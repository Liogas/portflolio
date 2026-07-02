#include "graphics/Camera.hpp"

Camera::Camera(void)
{
	this->_x = 0;
	this->_y = 0;
	std::cout << "Camera created" << std::endl;
}

Camera::~Camera()
{
	std::cout << "Camera destroyed" << std::endl;
}

void	Camera::setPos(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

int	Camera::getX() const
{
	return (this->_x);
}

int Camera::getY() const
{
	return (this->_y);
}

