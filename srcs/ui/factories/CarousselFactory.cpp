#include "CarousselFactory.hpp"

Caroussel	CarousselFactory::create(
	SDL_Rect	&container
)
{
	(void)container;
	Caroussel c;
	return (c);
}