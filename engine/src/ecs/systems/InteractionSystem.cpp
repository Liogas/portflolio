#include "InteractionSystem.hpp"

void	InteractionSystem(
	entt::registry		&registry,
	const InputSDL		&input,
	entt::dispatcher	&dispatcher
)
{
	if (!input.isKeyPressed(SDL_SCANCODE_E))
		return ;

	auto PlayerView = registry.view<PlayerTag, Position, Movement, Collider>();
	for (auto player : PlayerView)
	{
		auto &pos = PlayerView.get<Position>(player);
		auto &mov = PlayerView.get<Movement>(player);
		auto &col = PlayerView.get<Collider>(player);

		const int offset = 16;
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
				interactBox.x = static_cast<int>(pos.x) + col.width / 9;
				interactBox.y = centerY - offset / 2;
				break ;
			case EDirection2::RIGHT :
				interactBox.x = static_cast<int>(pos.x) + col.width / 1.5;
				interactBox.y = centerY - offset / 2;
				break ;
			case EDirection2::UP :
				interactBox.x =  centerX - offset / 2;
				interactBox.y = static_cast<int>(pos.y) + col.height / 9;
				break ;
			case EDirection2::DOWN :
				interactBox.x = centerX - offset / 2;
				interactBox.y = static_cast<int>(pos.y) + col.height / 1.5;
				break ;
			default : break ;
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
				dispatcher.trigger(
					InteractEvent{
						player,
						entity
					}
				);
			}
		}
	}
}