#ifndef GAME_HPP
# define GAME_HPP

#include <entt/entt.hpp>

#include "application/IGame.hpp"
#include "world/World.hpp"
#include "ui/manager/UIManager.hpp"
#include "computers/ComputerManager.hpp"
#include "projects/ProjectManager.hpp"
#include "config/ControlsConfig.hpp"

class Game : public IGame
{
	public:
		Game();
		void	init(RendererSDL &, entt::registry &) override;
		void	update(RendererSDL &, InputSDL &, float dt) override;
		void	render(RendererSDL &renderer) override;
		bool	isRunning() const override;
		void	onQuit(const QuitGameEvent &);
	private:
		entt::dispatcher	_dispatcher;
		ControlsConfig		_cfg;
		ComputerManager		_cm;
		ProjectManager		_pm;
		bool				_running;

		std::unique_ptr<ResourceManager>	_rm;
		std::unique_ptr<UIManager>			_uim;
		std::unique_ptr<World>				_world;
};

#endif