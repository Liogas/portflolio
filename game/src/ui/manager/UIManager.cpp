#include "UIManager.hpp"

UIManager::UIManager(
	ComputerManager 	&cm,
	ProjectManager		&pm,
	ResourceManager	&rm,
	RendererSDL			&renderer,
	entt::dispatcher	&dispatcher,
	ControlsConfig		&cfg
):
	_cm(cm),
	_pm(pm),
	_rm(rm),
	_renderer(renderer),
	_dispatcher(dispatcher),
	_cfg(cfg)
{
}

void	UIManager::openPortolio(
	std::string	&emit,
	std::string	&id
)
{
	auto ui = std::make_unique<PortfolioUI>(
		id,
		this->_cm,
		this->_rm,
		this->_pm,
		this->_renderer
	);
	this->push(std::move(ui));
}

void    UIManager::openPause(const OpenPauseMenuEvent &)
{
    // N'empile pas un deuxieme menu pause si un est deja ouvert
    for (auto &ui : this->_stack)
        if (dynamic_cast<PauseMenuUI*>(ui.get()))
            return ;
    auto ui = std::make_unique<PauseMenuUI>(this->_renderer, this->_rm, this->_dispatcher, this->_cfg);
    this->push(std::move(ui));
}

void    UIManager::changeResolution(const ChangeResolutionEvent &e)
{
    SDL_Window *win = this->_renderer.getWindow().getWindow();
    if (!win)
        return ;

    SDL_SetWindowSize(win, e.w, e.h);

    int displayIndex = SDL_GetWindowDisplayIndex(win);
    if (displayIndex < 0)
        displayIndex = 0;

    SDL_Rect bounds;
    if (SDL_GetDisplayUsableBounds(displayIndex, &bounds) != 0)
        SDL_GetDisplayBounds(displayIndex, &bounds); // fallback

    SDL_SetWindowPosition(
        win,
        bounds.x + (bounds.w - e.w) / 2,
        bounds.y + (bounds.h - e.h) / 2
    );
}

void	UIManager::bind(entt::dispatcher &dispatcher)
{
	dispatcher.sink<OpenPauseMenuEvent>().connect<&UIManager::openPause>(*this);
	dispatcher.sink<ChangeResolutionEvent>().connect<&UIManager::changeResolution>(*this);
	dispatcher.sink<ToggleFullScreenEvent>().connect<&UIManager::toggleFullscreen>(*this);
	dispatcher.sink<TriggerFiredEvent>().connect<&UIManager::onTrigger>(*this);
}

void	UIManager::onTrigger(const TriggerFiredEvent &e)
{
	if (e.emit == "portfolio_loading")
		this->openPortfolio(e.emit, e.id);
}

void	UIManager::closeTopWindow()
{

}

void	UIManager::push(std::unique_ptr<UIWindow> ui)
{
	this->_stack.push_back(std::move(ui));
}

void	UIManager::pop()
{
	if (!this->_stack.empty())
        this->_stack.pop_back();
}

void	UIManager::clear()
{
	this->_stack.clear();
}

void	UIManager::handleInput(const InputSDL &input)
{
	if (!this->_stack.empty())
		this->_stack.back()->handleInput(input);
}

void	UIManager::update(float dt)
{
	for (auto &ui : this->_stack)
		ui->update(dt);
	while (!this->_stack.empty() && this->_stack.back()->shouldClose())
		this->_stack.pop_back();
}

void	UIManager::render(RendererSDL &renderer)
{
	for (auto &ui : this->_stack)
		ui->render(renderer);
}

bool	UIManager::blocksGameplay() const
{
	for (const auto &ui : this->_stack)
	{
		if (ui->blocksGameplay())
			return (true);
	}
	return (false);
}

bool	UIManager::empty() const
{
	return (this->_stack.empty());
}

void    UIManager::toggleFullscreen(const ToggleFullScreenEvent &)
{
    SDL_Window *win = this->_renderer.getWindow().getWindow();
    if (!win)
        return;
    Uint32 flags = SDL_GetWindowFlags(win);
    SDL_SetWindowFullscreen(
        win,
        (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP
    );
}