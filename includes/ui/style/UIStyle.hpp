#ifndef UISTYLE_HPP
# define UISTYLE_HPP

# include <SDL2/SDL.h>
# include <string_view>

namespace UIStyle
{

	namespace	Computer
	{
		constexpr float	TitleHeight{20.f};
		constexpr float	CarousselHeight{60.f};
		constexpr float	Spacing{2.5f};
	}

	namespace	Caroussel
	{
		constexpr float	MainWidth{30.f};
		constexpr float MainHeight{90.f};
		constexpr float SideWidth{15.f};
		constexpr float	Spacing{5.f};
		constexpr float SideWidthRatio      = 0.6f;  // largeur carte latérale / largeur carte principale
		constexpr float SideNearHeightRatio = 0.85f; // hauteur du bord proche / hauteur carte principale
		constexpr float SideFarHeightRatio  = 0.7f;  // hauteur du bord loin / hauteur du bord proche
		constexpr float SideBrightness      = 0.55f; // luminosité des cartes latérales (1.0 = normal)
		constexpr int	CoverflowSlices		= 16;
	}

	namespace	Card
	{
		constexpr float	TitleHeight{15.f};
		constexpr float TitleSize{12.f};
		constexpr float	TagsHeight{15.f};
		constexpr float DescHeight{60.f};
		constexpr float DescSize{8.f};
		constexpr float	Spacing{2.5f};
		constexpr SDL_Color	BkgColor{
			70,
			70,
			70,
			255
		};
		constexpr SDL_Color	BorderColor{
			255,
			255,
			255,
			255
		};
		constexpr SDL_Color	TitleColor{
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
		return (static_cast<int>(value * percentage / 100.f));
	}
	
}

#endif