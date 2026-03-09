#include "App.hpp"

App::App():
	_running(false),
	_sdl(ESDLOption::VIDEO | ESDLOption::EVENTS),
	_window("test", 1280, 720, EWindowOption::SHOWN),
	_renderer(this->_window, ERendererOption::ACCELERATED),
	_input(),
	_event(),
	_ressources(this->_renderer)
{
	std::cout << "App created" << std::endl;
	this->_ressources.loadTest();
}

App::~App()
{
	std::cout << "App destroyed" << std::endl;
}

void	App::run()
{
	this->_running = true;
	while (this->_running)
	{
		this->handleEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
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