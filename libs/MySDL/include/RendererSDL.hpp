#ifndef	RENDERERSDL_HPP
# define RENDERERSDL_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <SDL_image.h>
# include <stdexcept>

# include "WindowSDL.hpp"

enum class ERendererOption : Uint32
{
	SOFTWARE 		= SDL_RENDERER_SOFTWARE,
	ACCELERATED 	= SDL_RENDERER_ACCELERATED,
	PRESENTVSYNC 	= SDL_RENDERER_PRESENTVSYNC,
	TARGETTEXTURE 	= SDL_RENDERER_TARGETTEXTURE
};

inline ERendererOption operator|(ERendererOption a, ERendererOption b)
{
    return static_cast<ERendererOption>(
        static_cast<Uint32>(a) | static_cast<Uint32>(b)
    );
}

class RendererSDL
{
	public:
		RendererSDL(WindowSDL &, ERendererOption);
		~RendererSDL(void);
		RendererSDL(const SDL_Renderer &) = delete;
		RendererSDL	&operator=(const SDL_Renderer &) = delete;
		// GETTERS
		[[nodiscard]] SDL_Renderer	*getRenderer() const;
		[[nodiscard]] WindowSDL		&getWindow() const;
		[[nodiscard]] int			getWidth() const;
		[[nodiscard]] int			getHeight() const;
		// SETTERS
		void	setSize(int w, int h);
		// METHODS
		void		clear();
		void		present();
		void		setDrawColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		SDL_Texture	*loadImg(const char * path);
	private:
		SDL_Renderer	*_renderer;
		WindowSDL		&_window;
		int				_width;
		int				_height;
};

#endif