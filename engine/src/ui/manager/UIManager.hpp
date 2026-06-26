#ifndef UIMANAGER_HPP
# define UIMANAGER_HPP

#include <vector>
#include <memory>

# include <entt/entt.hpp>

# include "ComputerUI.hpp"
# include "PauseMenuUI.hpp"

# include "RendererSDL.hpp"
# include "InputSDL.hpp"

#include "Events.hpp"

class UIManager
{
	public:
		UIManager(
			ComputerManager 	&cm,
			ProjectManager		&pm,
			ResourceManager	&rm,
			RendererSDL			&renderer,
			entt::dispatcher	&dispatcher,
			ControlsConfig		&cfg
		);
		void	openComputer(const OpenComputerEvent &e);
		void	closeTopWindow();
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
	private:
		std::vector<std::unique_ptr<UIWindow>>	_stack;
		ComputerManager							&_cm;
		ProjectManager							&_pm;
		ResourceManager						&_rm;
		RendererSDL								&_renderer;
		entt::dispatcher						&_dispatcher;
		ControlsConfig							&_cfg;
};

#endif