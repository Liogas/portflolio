#include "application/App.hpp"

#include <stdexcept>

#include "World.hpp"
#include "TestScene.hpp"
#include "InputSystem.hpp"

int main()
{
    try
    {
        App app;
        app.init();
        app.run();
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
}