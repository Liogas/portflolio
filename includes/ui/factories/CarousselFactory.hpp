#ifndef CAROUSSELFACTORY_HPP
# define CAROUSSELFACTORY_HPP

# include "Caroussel.hpp"
# include "UIStyle.hpp"
# include "RessourceManager.hpp"
# include "ProjectCardFactory.hpp"

class CarousselFactory
{
    public:
        CarousselFactory() = delete;
        static Caroussel    create(
            std::vector<std::string>	projectIds,
            const SDL_Rect				&container,
			RessourceManager			&rm,
			ProjectManager				&pm,
			RendererSDL					&renderer     
        );
};

#endif