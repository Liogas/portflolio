#ifndef INTERACTIONSYSTEM_HPP
# define INTERACTIONSYSTEM_HPP

# include <entt/entt.hpp>

# include "InputSDL.hpp"

# include "PlayerTag.hpp"
# include "Position.hpp"
# include "Movement.hpp"
# include "Collider.hpp"
# include "Interactable.hpp"
# include "DebugBox.hpp"

# include "World.hpp"

class World;

void	InteractionSystem(World &world, entt::registry &registry, const InputSDL &input);

#endif