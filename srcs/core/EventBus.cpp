#include "EventBus.hpp"

void	EventBus::emit(const Event &e)
{
	events.push_back(e);
}

void	EventBus::clear()
{
	events.clear();
}