#ifndef EVENTS_HPP
# define EVENTS_HPP

# include <entt/entt.hpp>

struct	InteractEvent
{
	entt::entity	source;
	entt::entity	target;
};

struct	CloseComputerEvent{};

struct TriggerFiredEvent
{
	std::string	emit;
	std::string	id;
};

struct TriggerEnteredEvent
{
	std::string	animation;
};

struct OpenComputerEvent {
	std::string id;
};
struct	OpenPauseMenuEvent {};
struct	QuitGameEvent {};
struct	ChangeResolutionEvent {int w; int h;};
struct	ToggleFullScreenEvent {};

#endif