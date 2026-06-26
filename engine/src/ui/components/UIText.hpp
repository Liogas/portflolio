#ifndef UITEXT_HPP
# define UITEXT_HPP

# include "UIElement.hpp"
# include <SDL2/SDL_ttf.h>

class UIText : public UIElement
{
	public:
		UIText();
		~UIText();
		UIText(const UIText&) = delete;
		UIText& operator=(const UIText&) = delete;

		UIText(UIText&& other) noexcept;
		UIText& operator=(UIText&& other) noexcept;
		void	setText(
			const std::string	&text,
			RendererSDL			&renderer,
			TTF_Font			*font,
			SDL_Color			color
		);
		void	draw(RendererSDL &renderer) override;
		void	setWrapWidth(int width);
	private:
		SDL_Texture	*_texture;
		int			_wrapWidth;
};

#endif