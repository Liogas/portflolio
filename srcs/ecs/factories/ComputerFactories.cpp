#include "ComputerFactories.hpp"


EDirection	getDir(std::string &dir)
{
	if (dir == "bottom")
		return (EDirection2::DOWN)
	else if (dir == "top")
		return (EDirection2::UP)
	else if (dir == "left")
		return (EDirection::LEFT)
	else if (dir == "right")
		return (EDirection::RIGHT)
	else
		return (EDirection::NONE);
}

static entt::entity	create(
	entt::registry	&registry,
	int				x,
	int				y,
	int				w,
	int				h,
	std::string		&direction
)
{
	auto computer = registry.create();
	registry.emplace<Position>(computer, x, y);
	registry.emplace<Collider>(computer, w, h);
	registry.emplace<ComputerTag>(computer);
	EDirection2	dir = getDir(direction);
	if (dir == EDirection::NONE)
		throw (std::runtime_error("ERROR ComputerFactories::create : Direction unknown"));
	registry.emplace<Interactable>(computer, dir);
	return (computer);
}