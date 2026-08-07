#include "ControlsManager.hpp"

const char	*actionToString(Action action)
{
	switch (action)
	{
		case Action::MoveLeft:			return "MoveLeft";
		case Action::MoveRight:			return "MoveRight";
		case Action::MoveDown:			return "MoveDown";
		case Action::MoveUp:			return "MoveUp";
		case Action::Interact:			return "Interact";
		case Action::OpenGithub:		return "OpenGithub";
		case Action::CarousselLeft:		return "CarousselLeft";
		case Action::CarousselRight:	return "CarousselRight";
		case Action::ScrollUp:			return "ScrollUp";
		case Action::ScrollDown:		return "ScrollDown";
		case Action::Pause:				return "Pause";
		case Action::Debug:				return "Debug";
		case Action::COUNT:				break ;
	}
	return "";
}

ControlsManager::ControlsManager(const std::string &configPath):
	_configPath(configPath)
{
	this->setDefaults();
}

void	ControlsManager::setDefaults()
{
	this->_config.bindings = {
		{ "Gauche",			SDL_SCANCODE_A },
		{ "Droite",			SDL_SCANCODE_D },
		{ "Haut",			SDL_SCANCODE_W },
		{ "Bas",			SDL_SCANCODE_S },
		{ "Interagir",		SDL_SCANCODE_E },
		{ "Ouvrir GitHub",	SDL_SCANCODE_RETURN },
		{ "Precedent",		SDL_SCANCODE_LEFT },
		{ "Suivant",		SDL_SCANCODE_RIGHT },
		{ "Scroll haut",	SDL_SCANCODE_UP },
		{ "Scroll bas",		SDL_SCANCODE_DOWN },
		{ "Pause",			SDL_SCANCODE_ESCAPE },
		{ "Debug",			SDL_SCANCODE_F3 },
	};
}

bool	ControlsManager::load()
{
	std::ifstream file(this->_configPath);
	if (!file.is_open())
		return (false);
	try
	{
		nlohmann::json	data;
		file >> data;
		const json &controls = data.at("controls");
		for (size_t i = 0; i < static_cast<size_t>(Action::COUNT); ++i)
		{
			Action action = static_cast<Action>(i);
			if (!controls.contains(actionToString(action)))
				continue ;
			std::string key = controls.at(actionToString(action));
			SDL_Scancide scancode = SDL_GetScancodeFromName(key.c_str());
			if (scancode != SDL_SCANCODE_UNKNOWN)
				this->_config.set(action, scancode);
		}
	} catch (const nlohmann::json::exception &)
	{
		return (false);
	}
	return (true);
}

bool	ControlsManager::save() const
{
	nlohmann::json data;
	for (size_t i = 0; i < static_cast<size_t>(Action::COUNT); ++i)
	{
		Action action = static_cast<Action>(i);
		SDL_Scancode scancode = this->_config.get(action);
		data["controls"][actionToString(action)] = SDL_GetScanCodeName(scancode);
	}
	std::ofstream file(this->_configPath);
	if (!file.is_open())
		return (false);
	file << data.dump(4);
	return (true);
}

SDL_Scancode	ControlsManager::get(Action action) const
{
	return (this->_config.get(action));
}

void	ControlsManager::set(Action action, SDL_Scancode scancode)
{
	this->_config.set(action, scancode);
}