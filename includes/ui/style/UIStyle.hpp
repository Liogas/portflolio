#ifndef UISTYLE_HPP
# define UISTYLE_HPP

# include <SDL2/SDL.h>
# include <string_view>

namespace UIStyle
{
	namespace	Card
	{
		constexpr SDL_Color	bkgColor{
			70,
			70,
			70,
			255
		};
		constexpr SDL_Color	borderColor{
			255,
			255,
			255,
			255
		};
		constexpr SDL_Color	titleColor{
			255,
			255,
			255,
			255
		};
		constexpr int	Padding{10};
		constexpr int	Spacing{10};
	}

    constexpr SDL_Color	BackgroundColor{
		30,
		30,
		30,
		200
	};
	constexpr SDL_Color	BorderColor{
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
	inline constexpr Font WC55{
		"WorkforceCombine.otf",
		55
	};
	inline constexpr Font KGSketch18{
		"KGSecondChancesSketch.ttf",
		18
	};
	inline constexpr Font KGSketch8{
		"KGSecondChancesSketch.ttf",
		8
	};
	inline constexpr Font KGSolid8{
		"KGSecondChancesSolid.ttf",
		8
	};

	inline void applyColor(SDL_Renderer *r, SDL_Color c)
	{
		SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
	}
}

#endif