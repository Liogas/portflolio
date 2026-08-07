#ifndef UIMANAGER_HPP
# define UIMANAGER_HPP

#include <vector>
#include <memory>

# include <entt/entt.hpp>

# include "ui/menus/portfolio/PortfolioUI.hpp"
# include "ui/menus/pauseMenu/PauseMenuUI.hpp"

# include "RendererSDL.hpp"
# include "InputSDL.hpp"

# include "computers/ComputerManager.hpp"
# include "projects/ProjectManager.hpp"

#include "events/Events.hpp"

class UIManager
{
	public:
		UIManager(
			ComputerManager 	&cm,
			ProjectManager		&pm,
			ResourceManager		&rm,
			RendererSDL			&renderer,
			entt::dispatcher	&dispatcher,
			ControlsConfig		&cfg
		);
		void	push(std::unique_ptr<UIWindow> ui);
		void	pop();
		void	clear();
		void	handleInput(const InputSDL &input);
		void	update(float dt);
		void	render(RendererSDL &renderer);
		bool	blocksGameplay() const;
		bool	empty() const;
		void	bind(entt::dispatcher &dispatcher);
		void	openPause(const OpenPauseMenuEvent &);
		void	changeResolution(const ChangeResolutionEvent &e);
		void    toggleFullscreen(const ToggleFullScreenEvent &);
		void	onTrigger(const TriggerFiredEvent &);
		void	openPortfolio(const std::string &emit, const std::string &id);
	private:
		std::vector<std::unique_ptr<UIWindow>>	_stack;
		ComputerManager							&_cm;
		ProjectManager							&_pm;
		ResourceManager							&_rm;
		RendererSDL								&_renderer;
		entt::dispatcher						&_dispatcher;
		ControlsConfig							&_cfg;
};

#endif