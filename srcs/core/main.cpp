#include "App.hpp"

#include <stdexcept>

// int	main(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	try
// 	{
// 		App app;
// 		app.run();
// 	} catch (const std::exception& e)
// 	{
// 		std::cerr << "ERROR : " << e.what() << std::endl;
// 	}
// 	return (0);
// }

#include "World.hpp"
#include "TestScene.hpp"
#include "InputSystem.hpp"

int main()
{
    try
    {
        App app;
        app.run();
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    // scene.load(registry);

    // float dt = 0.016f;

    // while (true)
    // {
    //     world.update(dt);

    //     auto view = registry.view<Position, PlayerTag>();
    //     for (auto e : view)
    //     {
    //         auto &p = view.get<Position>(e);
    //         std::cout << "Player: " << p.x << ", " << p.y << std::endl;
    //     }
    // }
}