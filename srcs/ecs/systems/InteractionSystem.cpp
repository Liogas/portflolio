#include "InteractionSystem.hpp"

void tmp(const EDirection2 &dir)
{
	switch (dir)
	{
		case EDirection2::LEFT : std::cout << "left" << std::endl; break ;
		case EDirection2::RIGHT : std::cout << "right" << std::endl; break ;
		case EDirection2::UP : std::cout << "up" << std::endl; break ;
		case EDirection2::DOWN : std::cout << "down" << std::endl; break ;
		default : std::cout << "none" << std::endl; break ;
	}
}

void	InteractionSystem(World &world, entt::registry &registry, const InputSDL &input)
{
	if (!input.isKeyPressed(SDL_SCANCODE_E))
		return ;

	auto PlayerView = registry.view<PlayerTag, Position, Movement, Collider>();
	for (auto player : PlayerView)
	{
		auto &pos = PlayerView.get<Position>(player);
		auto &mov = PlayerView.get<Movement>(player);
		auto &col = PlayerView.get<Collider>(player);

		const int offset = 64;
		SDL_Rect interactBox = {
			static_cast<int>(pos.x),
			static_cast<int>(pos.y),
			offset,
			offset
		};

		int centerX = static_cast<int>(pos.x) + col.width / 2;
		int centerY = static_cast<int>(pos.y) + col.height / 2;

		switch (mov.lastDirection)
		{
			case EDirection2::LEFT :
				interactBox.x = static_cast<int>(pos.x) - offset;
				interactBox.y = centerY - offset / 2;
				break ;
			case EDirection2::RIGHT :
				interactBox.x = static_cast<int>(pos.x) + col.width;
				interactBox.y = centerY - offset / 2;
				break ;
			case EDirection2::UP :
				interactBox.x =  centerX - offset / 2;
				interactBox.y = static_cast<int>(pos.y) - offset;
				break ;
			case EDirection2::DOWN :
				interactBox.x = centerX - offset / 2;
				interactBox.y = static_cast<int>(pos.y) + col.height;
				break ;
			default : break ;
		}
		if (world.debug)
		{
			registry.emplace_or_replace<DebugBox>(
				player,
				DebugBox{interactBox, SDL_Color{255, 0, 0, 255}}
			);
		}
		auto interactables = registry.view<Interactable, Position, Collider>();
		for (auto entity : interactables)
		{
			if (entity == player)
				continue ;
			auto &targetPos = interactables.get<Position>(entity);
			auto &targetCol = interactables.get<Collider>(entity);
			auto &inter = interactables.get<Interactable>(entity);
			SDL_Rect targetBox = {
				static_cast<int>(targetPos.x),
				static_cast<int>(targetPos.y),
				targetCol.width,
				targetCol.height
			};
			if (SDL_HasIntersection(
				&interactBox,
				&targetBox
			) && inter.direction == mov.lastDirection)
			{
				std::cout << "Interaction detected !" << std::endl;
			}
		}
	}
}