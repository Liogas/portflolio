#include "App.hpp"

App::App():
	_sdl(ESDLOption::VIDEO | ESDLOption::EVENTS),
	_window("test", 1280, 720, EWindowOption::SHOWN),
	_

{
	std::cout << "App created" << std::endl;
}

App::~App()
{
	std::cout << "App destroyed" << std::endl;
}

void	App::run()
{
	while (this->_running)
	{
		this->handleEvents();
		
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(16));
}

void	App::handleEvents()
{
	SDL_Event	e;
	while (this->_event.poll(&e))
	{
		if (e.type == SDL_QUIT)
			this->_running = false;
	}
	this->_input.update();
}