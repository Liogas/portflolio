#include "UIManager.hpp"

UIManager::UIManager(
	ComputerManager 	&cm,
	ProjectManager		&pm,
	RessourceManager	&rm,
	RendererSDL			&renderer
):
	_cm(cm),
	_pm(pm),
	_rm(rm),
	_renderer(renderer)
{
	this->_cm = cm;
	this->_pm = pm;
	this->_rm = rm;
	this->_renderer = renderer;
}

void	UIManager::openComputer(const OpenComputerEvent &e)
{
	auto ui = std::make_unique<ComputerUI>(e.computerId, this->_cm);
	ui->init(this->_rm, this->_renderer, this->_pm);
	this->push(std::move(ui));
}

void	UIManager::bind(entt::dispatcher &dispatcher)
{
	dispatcher.sink<OpenComputerEvent>().connect<&UIManager::openComputer>(*this);
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