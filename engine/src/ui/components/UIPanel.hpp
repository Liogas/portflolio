#ifndef UIPANEL_HPP
# define UIPANEL_HPP

# include "UIElement.hpp"

class UIPanel : public UIElement
{
	public:
		void	draw(RendererSDL &r) override;
		SDL_Color	background;
		SDL_Color	border;
};

#endif