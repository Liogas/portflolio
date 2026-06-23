#ifndef EVENTBUS_HPP
# define EVENTBUS_HPP

# include <entt/entt.hpp>

# include <vector>

struct	InteractEvent
{
	entt::entity	source;
	entt::entity	target;
};

struct	CloseComputerEvent{};

struct	OpenComputerEvent
{
	std::string	computerId;
};

class EventBus
{
	public:
		void	emit(const Event &e);
		void	clear();
		std::vector<Event> events;
};

#endif