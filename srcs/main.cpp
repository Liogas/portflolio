#include "AppSDL.hpp"
#include "WindowSDL.hpp"
#include "RendererSDL.hpp"
#include <stdexcept>
#include <chrono>
#include <thread>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	try
	{
		AppSDL	sdl(ESDLOption::EVENTS | ESDLOption::VIDEO);
		WindowSDL	window("Test", 1280, 720, EWindowOption::SHOWN);
		RendererSDL	renderer(window, ERendererOption::ACCELERATED);
		while (1)
		{
			SDL_PumpEvents();
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_K])
			{
				std::cout << "Touche K appuyee" << std::endl;
				break ;
			}
			else if (state[SDL_SCANCODE_J])
				window.setFullScreen();
			else if (state[SDL_SCANCODE_Q])
			{
				renderer.setDrawColor(125,125,125,255);
				renderer.clear();
				renderer.present();
			}
			else if (state[SDL_SCANCODE_W])
			{
				renderer.setDrawColor(25,25,25,255);
				renderer.clear();
				renderer.present();
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	} catch (error_t error)
	{
		std::cerr << "ERROR : " << error << std::endl;
	}
	return (0);
}