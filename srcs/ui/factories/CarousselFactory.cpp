#include "CarousselFactory.hpp"

Caroussel	CarousselFactory::create(
	std::vector<std::string>	projectIds,
	const SDL_Rect				&container,
	RessourceManager			&rm,
	ProjectManager				&pm,
	RendererSDL					&renderer
)
{
	Caroussel c;
	c.rect = {
		container.x,
		container.y + static_cast<int>(container.h * 0.2f),
		container.w,
		static_cast<int>(container.h * 0.8f)
	};
	c.visibleCards = 3;
	c.spacing = 20;
	for (size_t i = 0; i < projectIds.size(); ++i)
	{
		bool s = (i == 0);
		c.cards.push_back(ProjectCardFactory::create(
			pm,
			rm,
			projectIds[i],
			renderer
		));
	}
	return (c);
}