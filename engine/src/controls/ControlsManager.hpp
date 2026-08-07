#ifndef CONTROLSMANAGER_HPP
# define CONTROLSMANAGER_HPP

# include "config/ControlsConfig.hpp"

class ControlsManager
{
	public:
		ControlsManager(const std::string &configPath);

		bool 					load();
		bool					save() const;

		SDL_Scancode 			get(Action action) const;
		void					set(Action action, SDL_Scancode scancode);

		const ControlsConfig	&getConfig() const;
	
	private:
		std::string		_configPath;
		ControlsConfig	_config;
		void			setDefaults();
}

#endif