#ifndef TITLEBARFACTORY_HPP
# define TITLEBARFACTORY_HPP

# include <SDL2/SDL_ttf.h>

# include "TitleBar.hpp"
# include "RendererSDL.hpp"
# include "RessourceManager.hpp"
# include "UIStyle.hpp"

class TitleBarFactory
{
	public:
		TitleBarFactory() = delete;
		static TitleBar	create(
			const std::string 		&title,
			SDL_Rect 				&container,
			RessourceManager		&rm,
			const RendererSDL		&renderer
		);
};

#endif