#include "App.hpp"

App::App():
	_running(false),
	_sdl(ESDLOption::VIDEO | ESDLOption::EVENTS),
	_window("coucou", 1280, 720, EWindowOption::SHOWN),
	_renderer(this->_window, ERendererOption::ACCELERATED | ERendererOption::PRESENTVSYNC | ERendererOption::TARGETTEXTURE),
	_input(),
	_event(),
	_rm(this->_renderer),
	_pm(),
	_cm(),
	_world(this->_rm, this->_cm, this->_pm)
{
	try
	{
		SDL_RenderSetLogicalSize(this->_renderer.getRenderer(), 640, 360);
		this->_renderer.setSize(640, 360);
		this->_pm.loadAll();
		this->_cm.loadAll();
		std::cout << "App created" << std::endl;
	} catch (const std::exception &e)
	{
		throw (std::runtime_error(e.what()));
	}
}

App::~App()
{
	std::cout << "App destroyed" << std::endl;
}

void	App::init()
{
	try
	{
		this->_world.changeScene(std::make_unique<TestScene>(
			this->_window.getWidth(), this->_window.getHeight()
		));
	} catch (const std::exception &e)
	{
		throw (std::runtime_error(e.what()));
	}
}

void	App::run()
{
	try
	{
		this->_running = true;
		auto lastTime 	= std::chrono::high_resolution_clock::now();
		while (this->_running)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
    		float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
    		lastTime = currentTime;
			this->_input.update();
			this->handleEvents();
			this->_renderer.setDrawColor(0, 0, 0, 255);
			this->_renderer.clear();
			this->_world.update(this->_input, deltaTime, this->_renderer);
			this->_world.render(this->_renderer);
			this->_renderer.present();
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	} catch (const std::exception& e)
	{
		throw (std::runtime_error(e.what()));
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
}
