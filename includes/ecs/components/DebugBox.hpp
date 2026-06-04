#ifndef DEBUGINTERACTION_HPP
# define DEBUGINTERACTION_HPP

# include <SDL2/SDL.h>

/*
	RED : Interactable
	BLUE : Collider
*/

typedef struct s_debugBox
{
	SDL_Rect box;
	SDL_Color color;
}	DebugBox;

#endif