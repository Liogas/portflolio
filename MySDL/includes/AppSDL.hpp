#ifndef APPSDL_HPP
# define APPSDL_HPP

# include <iostream>
# include <SDL2/SDL.h>
# include <stdexcept>

enum class ESDLOption : Uint32
{
    TIMER			= SDL_INIT_TIMER,
	AUDIO			= SDL_INIT_AUDIO,
	VIDEO			= SDL_INIT_VIDEO,
	JOYSTICK		= SDL_INIT_JOYSTICK,
	HAPTIC			= SDL_INIT_HAPTIC,
	GAMECONTROLLER	= SDL_INIT_GAMECONTROLLER,
	EVENTS			= SDL_INIT_EVENTS,
	EVERYTHING		= SDL_INIT_EVERYTHING,
	NOPARACHUTE		= SDL_INIT_NOPARACHUTE
};

inline ESDLOption operator|(ESDLOption a, ESDLOption b)
{
    return static_cast<ESDLOption>(
        static_cast<Uint32>(a) | static_cast<Uint32>(b)
    );
}

class AppSDL
{
    public:
        AppSDL(ESDLOption);
        ~AppSDL();
		AppSDL(const AppSDL &) = delete;
		AppSDL &operator=(const AppSDL &) = delete;
    private:

};

#endif