#include "App.hpp"

App::App():
	_running(false),
	_sdl(ESDLOption::VIDEO | ESDLOption::EVENTS),
	_window("test", 1280, 720, EWindowOption::SHOWN),
	_renderer(this->_window, ERendererOption::ACCELERATED | ERendererOption::PRESENTVSYNC | ERendererOption::TARGETTEXTURE),
	_input(),
	_event(),
	_ressources(this->_renderer),
	_player(this->_ressources.getTexture("srcs/imgs/char1.png"), 64, 64)
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
		this->_player.getSprite().setSrcPosition(0, 64 * 2);
		this->_player.getSprite().setDestPosition(0, 0);

		while (this->_running)
		{
			this->handleEvents();
			this->_renderer.setDrawColor(0, 0, 0, 255);
			this->_renderer.clear();

			// update player
			this->update();
			this->render();

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

void	App::update()
{
	if (this->_input.isKeyPressed(SDL_SCANCODE_D))
		this->_player.move();
}

void	App::render()
{
	this->_player.render();
	this->_renderer.present();
}
