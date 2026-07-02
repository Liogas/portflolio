#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <array>

enum class Action
{
    MoveLeft, MoveRight, MoveUp, MoveDown,
    Interact, OpenGithub,
    CarousselLeft, CarousselRight,
    ScrollUp, ScrollDown,
    Pause, Debug,
    COUNT
};

struct ControlEntry
{
    std::string     label;      // affichage dans le menu
    SDL_Scancode    scancode;
};

struct ControlsConfig
{
    std::array<ControlEntry, (int)Action::COUNT> bindings = {{
        { "Gauche",			SDL_SCANCODE_A      },
        { "Droite",			SDL_SCANCODE_D      },
        { "Haut",			SDL_SCANCODE_W      },
        { "Bas",			SDL_SCANCODE_S      },
        { "Interagir",		SDL_SCANCODE_E      },
        { "Ouvrir GitHub",	SDL_SCANCODE_RETURN },
        { "Caroussel <",	SDL_SCANCODE_LEFT   },
        { "Caroussel >",	SDL_SCANCODE_RIGHT  },
        { "Scroll haut",	SDL_SCANCODE_UP     },
        { "Scroll bas",		SDL_SCANCODE_DOWN   },
        { "Pause",			SDL_SCANCODE_ESCAPE },
		{ "Debug",			SDL_SCANCODE_F3		}
    }};

    SDL_Scancode get(Action a) const
    {
        return this->bindings[(int)a].scancode;
    }

    void set(Action a, SDL_Scancode sc)
    {
        this->bindings[(int)a].scancode = sc;
    }
};