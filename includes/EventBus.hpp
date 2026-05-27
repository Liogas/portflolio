#ifndef EVENTBUS_HPP
# define EVENTBUS_HPP

# include <entt/entt.hpp>

# include <vector>

typedef struct s_event
{
	enum class Type
	{
		Interact,
		Damage,
		Trigger
	};
	Type			type;
	entt::entity	source{};
	entt::entity	target{};
}	Event;

class EventBus
{
	public:
		void	emit(const Event &e);
		void	clear();
		std::vector<Event> events;
};

#endif