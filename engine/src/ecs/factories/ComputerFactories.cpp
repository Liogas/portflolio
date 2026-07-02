#include "ecs/factories/ComputerFactories.hpp"


static EDirection2	getDir(const std::string &dir)
{
	if (dir == "bottom")
		return (EDirection2::DOWN);
	else if (dir == "top")
		return (EDirection2::UP);
	else if (dir == "left")
		return (EDirection2::LEFT);
	else if (dir == "right")
		return (EDirection2::RIGHT);
	else
		return (EDirection2::NONE);
}


entt::entity	ComputerFactories::create(
	entt::registry		&registry,
	const std::string	&id,
	float				x,
	float				y,
	int					w,
	int					h,
	const std::string	&direction
)
{
	auto computer = registry.create();
	registry.emplace<Position>(computer, x, y);
	registry.emplace<Collider>(computer, w, h);
	registry.emplace<Computer>(
		computer, Computer
		{
			id,
		 	false
		}
	);
	EDirection2	dir = getDir(direction);
	if (dir == EDirection2::NONE)
		throw (std::runtime_error("ERROR ComputerFactories::create : Direction unknown"));
	registry.emplace<Interactable>(computer, dir);
	return (computer);
}