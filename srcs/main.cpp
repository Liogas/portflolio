#include <SDL2/SDL.h>

#include <stdio.h>

#include <iostream>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Création de la fenêtre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  640,
                                                                  480,
                                                                  SDL_WINDOW_SHOWN);
                                                                  
        int fullscreen = 0;

        // On récupère le nombre de modes d'affichage pour l'écran 0 /////
        int modeNumber = SDL_GetNumDisplayModes(0);
        if (modeNumber < 0)
        {
            fprintf(stdout,"Échec lors de la récupération du nombre de modes (%s)\n",SDL_GetError());
            return -2;
        }
        fprintf(stdout,"Vous avez %d mode(s) d'affichage\n", modeNumber);

        // Affichage des différents modes
        SDL_DisplayMode displayMode;
        int error;
        for (int i = 0 ; i < modeNumber ; i++)
        {
            error = SDL_GetDisplayMode(0, i, &displayMode);
            if (error < 0)
            {
                fprintf(stdout, "Échec lors de la récupération du mode d'affichage (%s)\n", SDL_GetError());
                return -3;
            }
            
            fprintf(stdout, "Mode %d : %dx%dx%d\n", i, displayMode.w, displayMode.h, displayMode.refresh_rate);
        }
        ////////////////////////////////////////////////////////////////////////
        while ( pWindow )
        {
            SDL_Event event;
            while (SDL_PollEvent(&event)) // Récupération des actions de l'utilisateur
            {
                switch(event.type)
                {
                    case SDL_QUIT: // Clic sur la croix
                        // quit=1;
                        SDL_DestroyWindow(pWindow);
                        pWindow = NULL;
                        break;
                    case SDL_KEYUP: // Relâchement d'une touche
                        if ( event.key.keysym.sym == SDLK_f ) // Touche f
                        {
                            // Alterne du mode plein écran au mode fenêtré
                            if ( fullscreen == 0 )
                            {
                                fullscreen = 1;
                                SDL_SetWindowFullscreen(pWindow,SDL_WINDOW_FULLSCREEN);
                            }
                            else if ( fullscreen == 1 )
                            {
                                fullscreen = 0;
                                SDL_SetWindowFullscreen(pWindow,0);
                            }
                        }
                        break;
                }
            }
        }
    }

    SDL_Quit();

    return 0;
}