#ifndef UISTYLE_HPP
# define UISTYLE_HPP

# include <SDL2/SDL.h>
# include <string_view>

namespace UIStyle
{
    constexpr SDL_Color	BackgroundColor{
		30,
		30,
		30,
		200
	};

	constexpr SDL_Color BorderColor{
		255,
		255,
		255,
		255
	};
	struct Font
	{
		std::string_view 	path;
		int					size;
	};
	inline constexpr Font Title{
		"WorkforceCombine.otf",
		55
	};
	inline constexpr Font Body{
		"KGSecondChancesSketch.ttf",
		18
	};
	inline constexpr Font Small{
		"KGSecondChancesSketch.ttf",
		12
	};
	inline void applyColor(SDL_Renderer *r, SDL_Color c)
	{
		SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
	}
}

#endif