#include "CarousselFactory.hpp"

Caroussel	CarousselFactory::create(
	std::vector<std::string>	projectIds,
	const SDL_Rect				&container,
	RessourceManager			&rm,
	const ProjectManager		&pm,
	RendererSDL					&renderer
)
{
	Caroussel c;
	try
	{
		c.rect = {
			container.x,
			container.y + static_cast<int>(container.h * 0.2f),
			container.w,
			static_cast<int>(container.h * 0.8f)
		};
		c.visibleCards = 3;
		c.spacing = 20;
		c.selectedCard = 1;
		c.cards.reserve(projectIds.size());
		for (size_t i = 0; i < projectIds.size(); ++i)
		{
			c.cards.push_back(ProjectCardFactory::create(
				pm,
				rm,
				projectIds[i],
				renderer
			));
			c.cards.back().init();
		}
		layoutCaroussel(c);
	} catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw (std::runtime_error("deidjeidj"));
    }
	return (c);
}