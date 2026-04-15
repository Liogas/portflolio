#ifndef ENTITY_HPP
# define ENTITY_HPP

# include "Camera.hpp"

typedef struct s_rect
{
	int x;
	int y;
	int width;
	int height;
}	t_rect;

class Entity
{
	public:
		virtual ~Entity() = default;
		// METHODS
		virtual void	update(float deltaTime) = 0;
		virtual void	interact(const Entity &e) = 0;
		[[nodiscard]] int	getX() const { return (this->_x); }
		[[nodiscard]] int	getY() const { return (this->_y); }
		[[nodiscard]] int	getHeight() const { return (this->_height); }
		[[nodiscard]] int	getWidth() const { return (this->_width); }
		bool	intersects(t_rect r) const {
			bool xOverlap = _x < r.x + r.width && _x + _width > r.x;
    		bool yOverlap = _y < r.y + r.height && _y + _height > r.y;
    		return (xOverlap && yOverlap);
		}
		void	setPos(int x, int y) { this->_x = x; this->_y = y; }
	protected:
		int		_x;
		int		_y;
		int		_height;
		int		_width;
};

#endif