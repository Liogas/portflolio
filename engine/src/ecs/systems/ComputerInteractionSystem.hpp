#ifndef COMPUTERINTERACTIONSYSTEM_HPP
# define COMPUTERINTERACTIONSYSTEM_HPP

# include <entt/entt.hpp>
# include "events/Events.hpp"
# include "ecs/components/Computer.hpp"

class ComputerInteractionSystem
{
    public:
        ComputerInteractionSystem(
            entt::dispatcher    &dispatcher,
            entt::registry      &registry
        );
        void    onInteract(const InteractEvent &e);
    private:
		entt::dispatcher	&_dispatcher;
        entt::registry		&_registry;
};

#endif