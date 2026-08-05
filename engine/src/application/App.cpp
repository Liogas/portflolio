#include "application/App.hpp"

App::App(int width, int height, const std::string &title):
	_sdl(ESDLOption::VIDEO | ESDLOption::EVENTS),
	_window(title.c_str(), width, height, EWindowOption::SHOWN),
	_renderer(this->_window, ERendererOption::ACCELERATED | ERendererOption::PRESENTVSYNC | ERendererOption::TARGETTEXTURE)
{
	SDL_RenderSetLogicalSize(this->_renderer.getRenderer(), 640, 360);
	this->_renderer.setSize(640, 360);
}

App::~App()
{
	std::cout << "App destroyed" << std::endl;
}

void	App::run(std::unique_ptr<IGame> game)
{
	InputSDL	input;
	Uint32		lastTime = SDL_GetTicks();
	game->init(this->_renderer, this->_registry);
	while (game->isRunning())
	{
		Uint32 now = SDL_GetTicks();
		float	dt = (now - lastTime) / 1000.f;
		lastTime = now;
		input.update();
		game->update(this->_renderer, input, dt);
		SDL_SetRenderDrawColor(this->_renderer.getRenderer(), 0, 0, 0, 0);
		SDL_RenderClear(this->_renderer.getRenderer());
		game->render(this->_renderer);
		SDL_RenderPresent(this->_renderer.getRenderer());
	}
}
