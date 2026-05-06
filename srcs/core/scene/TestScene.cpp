#include "TestScene.hpp"

TestScene::TestScene()
{
    std::cout << "TestScene created" << std::endl;
}

void	TestScene::load(entt::registry &registry)
{
	auto player = registry.create();

	registry.emplace<Position>(player, 550.f, 280.f);
	registry.emplace<Movement>(player, 200.f, EDirection2::NONE, EDirection2::NONE, false);
	registry.emplace<PlayerTag>(player);
}