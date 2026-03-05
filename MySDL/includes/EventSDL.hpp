#ifndef EVENTSDL_HPP
# define EVENTSDL_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <stdexcept>

class EventSDL
{
	public:
		EventSDL();
		~EventSDL();
		EventSDL(const EventSDL &) = delete;
		EventSDL	&operator=(const EventSDL &) = delete;
		bool	poll(SDL_Event *);
	private:
};

#endif