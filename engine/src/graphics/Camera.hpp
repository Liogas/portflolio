#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <iostream>

class Camera
{
	public:
		Camera(void);
		~Camera();
		// GETTERS
		[[nodiscard]] int	getX() const;
		[[nodiscard]] int	getY() const;
		// METHODS
		void	setPos(int x, int y);
	private:
		int	_x;
		int	_y;
};

#endif