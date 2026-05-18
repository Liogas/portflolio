#include "App.hpp"

App::App():
	_running(false),
	_sdl(ESDLOption::VIDEO | ESDLOption::EVENTS),
	_window("test", 1280, 720, EWindowOption::SHOWN),
	_renderer(this->_window, ERendererOption::ACCELERATED | ERendererOption::PRESENTVSYNC | ERendererOption::TARGETTEXTURE),
	_input(),
	_event(),
	_rm(this->_renderer),
	_sm(this->_rm),
	_world(this->_rm, this->_sm)
{
	SDL_RenderSetLogicalSize(this->_renderer.getRenderer(), 640, 360);
	this->_renderer.setSize(640, 360);
	std::cout << "App created" << std::endl;
}

App::~App()
{
	std::cout << "App destroyed" << std::endl;
}

void	App::init()
{
	try
	{
		this->_world.init();
		this->_sceneManager.changeScene(std::make_unique<TestScene>(
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

			this->handleEvents();
			this->_world.update(this->_input, dt);
			this->_world.render();

			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	} catch (const std::exception& e)
	{
		throw (std::runtime_error(e.what()));
	}
}

// void	App::run()
// {
// 	try
// 	{
// 		this->_running	= true;
// 		auto lastTime 	= std::chrono::high_resolution_clock::now();
// 		this->_sceneManager.changeScene(std::make_unique<GameScene>(this->_window.getWidth(), this->_window.getHeight()), this->_gameState);
// 		while (this->_running)
// 		{
// 			auto currentTime = std::chrono::high_resolution_clock::now();
//     		float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
//     		lastTime = currentTime;

// 			this->handleEvents();
// 			this->_renderer.setDrawColor(0, 0, 0, 255);
// 			this->_renderer.clear();

// 			this->_sceneManager.handleEvent(this->_event, this->_gameState);
// 			this->_sceneManager.update(this->_input, this->_gameState, deltaTime);
// 			this->_sceneManager.render(this->_renderer, this->_gameState);

// 			std::this_thread::sleep_for(std::chrono::milliseconds(16));
// 		}
// 	} catch (const std::exception &e)
// 	{
// 		throw std::runtime_error(e.what());
// 	}
// }

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
