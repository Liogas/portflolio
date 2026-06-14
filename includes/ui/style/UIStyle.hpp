#ifndef UISTYLE_HPP
# define UISTYLE_HPP

# include <SDL2/SDL.h>
# include <string_view>

namespace UIStyle
{

	namespace	Computer
	{
		constexpr float	TitleHeight{20};
		constexpr float	CarousselHeight{60};
		constexpr float	Spacing{10};
	}

	namespace	Caroussel
	{
		constexpr float	MainWidth{50};
		constexpr float MainHeight{90};
		constexpr float SideWidth{15};
		constexpr float	Spacing{5};
	}

	namespace	Card
	{
		constexpr float	TitleHeight{15};
		constexpr float TitleSize{12};
		constexpr float	TagsHeight{15};
		constexpr float DescHeight{60};
		constexpr float DescSize{8};
		constexpr float	Spacing{2.5};
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

	

	namespace	Font
	{
		struct s_font
		{
			std::string_view 	path;
			int					size;
		};
		inline constexpr s_font WC55{
			"WorkforceCombine.otf",
			55
		};
		inline constexpr s_font KGSketch18{
			"KGSecondChancesSketch.ttf",
			18
		};
		inline constexpr s_font KGSolid12{
			"KGSecondChancesSolid.ttf",
			12
		};
		inline constexpr s_font KGSketch8{
			"KGSecondChancesSketch.ttf",
			8
		};
		inline constexpr s_font KGSolid8{
			"KGSecondChancesSolid.ttf",
			8
		};
	}
	inline void applyColor(SDL_Renderer *r, SDL_Color c)
	{
		SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
	}

	inline int	applyPercentage(float percentage, int value)
	{
		return (value * percentage);
	}
	
}

#endif