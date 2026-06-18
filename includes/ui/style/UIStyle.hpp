#ifndef UISTYLE_HPP
# define UISTYLE_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <string_view>

namespace UIStyle
{

	namespace	Computer
	{
		namespace	Title
		{
			constexpr const char	*Font	= "WorkforceCombine.otf";
			constexpr int			Size	= 55;
			constexpr SDL_Color		Color	{255,255,255,255};
			constexpr float			Height	= 20.f;
		}
		constexpr float		Height			= 75.f;
		constexpr float		Spacing			= 2.5f;
    	constexpr SDL_Color	BackgroundColor	{30,30,30,200};
		constexpr SDL_Color	BorderColor		{255,255,255,255};
	}

	namespace	Caroussel
	{
		constexpr int	Height				= 80.f;
		constexpr float	CardWidth			= 30.f;
		constexpr float CardHeight			= 80.f;
		constexpr float SideWidth			= 15.f;
		constexpr float	Spacing				= 2.5f;
		constexpr float SideWidthRatio      = 0.6f; 
		constexpr float SideNearHeightRatio = 0.85f;
		constexpr float SideFarHeightRatio  = 0.7f;
		constexpr float SideBrightness      = 0.55f;
		constexpr int	CoverflowSlices		= 16;
		namespace	Pagination
		{
			constexpr const char	*Font	= "KGSecondChancesSolid.ttf";
			constexpr int			Size	= 10;
			constexpr SDL_Color		Color	= {255,255,255,200};
		}
	}

	namespace	Card
	{
		namespace	Title
		{
			constexpr float			Height	= 15.f;
			constexpr int 			Size	= 16;
			constexpr const char	*Font	= "KGSecondChancesSketch.ttf";
			constexpr SDL_Color		Color	{255,255,255,255};
		}
		namespace	Desc
		{
			constexpr int 			Size	= 8;
			constexpr const char	*Font	= "KGSecondChancesSolid.ttf";
			constexpr SDL_Color		Color	{255,255,255,255};
			constexpr int			Height	= 25.f;
		}
		namespace	Img
		{
			constexpr float	Height	= 45.f;
			constexpr float Width	= 80.f;
		}
		namespace	Tags
		{
			constexpr float	Height	= 5.f;
		}
		constexpr float		Spacing		= 5.f;
		constexpr SDL_Color	BkgColor	{70,70,70,255};
		constexpr SDL_Color	BorderColor	{255,255,255,255};
	}

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