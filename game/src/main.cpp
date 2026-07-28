#include "application/App.hpp"

#include <stdexcept>

#include "world/World.hpp"
#include "world/Game.hpp"
#include "ecs/systems/InputSystem.hpp"

int main()
{
    try
    {
        App app(1280, 720, "Portfolio");
        app.run(std::make_unique<Game>());
        return (0);
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
}