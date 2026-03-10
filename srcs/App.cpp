#include "App.hpp"

App::App():
	_running(false),
	_sdl(ESDLOption::VIDEO | ESDLOption::EVENTS),
	_window("test", 1280, 720, EWindowOption::SHOWN),
	_renderer(this->_window, ERendererOption::ACCELERATED | ERendererOption::PRESENTVSYNC | ERendererOption::TARGETTEXTURE),
	_input(),
	_event(),
	_ressources(this->_renderer)
{
	std::cout << "App created" << std::endl;
}

App::~App()
{
	std::cout << "App destroyed" << std::endl;
}

void	App::run()
{
	try
	{
		this->_running = true;
		Player player(this->_ressources.getTexture("srcs/imgs/char1.png"), 64, 64);
		player.getSprite().setSrcPosition(0, 64 * 2);
		player.getSprite().setDestPosition(0, 0);

		Player player2(this->_ressources.getTexture("srcs/imgs/char1.png"), 64, 64);
		player2.getSprite().setSrcPosition(0, 64 * 3);
		player2.getSprite().setDestPosition(0, 128);
		while (this->_running)
		{
			this->handleEvents();
			this->_renderer.setDrawColor(0, 0, 0, 255);
			this->_renderer.clear();

			// update player
			player.render();
			player2.render();
			this->_renderer.present();

			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	} catch (const std::exception &e)
	{
		throw std::runtime_error(e.what());
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
