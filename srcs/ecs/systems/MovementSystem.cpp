#include "MovementSystem.hpp"

void MovementSystem(World &world, entt::registry& registry)
{
    if (world.gameState != GameState::Playing)
		return ;

    auto view = registry.view<Movement, Velocity>();

    for (auto e : view)
    {
        auto &vel = view.get<Velocity>(e);
        auto &mov = view.get<Movement>(e);

        vel.x = 0;
        vel.y = 0;

        mov.isMoving = true;
        switch (mov.direction)
        {
            case EDirection2::LEFT:		vel.x = -mov.speed; break;
            case EDirection2::RIGHT:	vel.x = mov.speed; break;
            case EDirection2::UP:		vel.y = -mov.speed; break;
            case EDirection2::DOWN:		vel.y = mov.speed; break;
            default:					mov.isMoving = false; break;
        }
    }
}
