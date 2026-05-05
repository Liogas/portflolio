#include "Position.hpp"
#include "Movement.hpp"
# include <entt/entt.hpp>

void MovementSystem(entt::registry& registry, float dt)
{
    auto view = registry.view<Position, Movement>();

    for (auto e : view)
    {
        auto &pos = view.get<Position>(e);
        auto &mov = view.get<Movement>(e);

        float vx = 0;
        float vy = 0;

        switch (mov.direction)
        {
            case EDirection2::LEFT:  vx = -mov.speed; break;
            case EDirection2::RIGHT: vx = mov.speed; break;
            case EDirection2::UP:    vy = -mov.speed; break;
            case EDirection2::DOWN:  vy = mov.speed; break;
            default: break;
        }

        pos.x += vx * dt;
        pos.y += vy * dt;
    }
}
