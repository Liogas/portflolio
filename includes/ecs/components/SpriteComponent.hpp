#ifndef SPRITECOMPONENT_HPP
# define SPRITECOMPONENT_HPP

# include "Sprite.hpp"

typedef struct s_spriteComponent
{
	std::shared_ptr<TextureSDL>	texture;
	int							width;
	int							height;
	SDL_Rect					src;
}	SpriteComponent;

#endif