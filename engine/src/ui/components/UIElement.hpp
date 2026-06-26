#ifndef UIELEMENT_HPP
# define UIELEMENT_HPP

# include "RendererSDL.hpp"

# include <vector>

enum class LayoutType
{
	Horizontal,
	Vertical
};

class UIElement
{
	public:
		virtual ~UIElement() = default;
		virtual void	draw(RendererSDL& renderer) = 0;
		SDL_Rect	rect;
};

#endif