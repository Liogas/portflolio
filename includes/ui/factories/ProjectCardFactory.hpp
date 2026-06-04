#ifndef PROJECTCARDFACTORY_HPP
# define PROJECTCARDFACTORY_HPP

# include "ProjectCard.hpp"
# include "ProjectManager.hpp"
# include "UIStyle.hpp"

# include <SDL2/SDL_ttf.h>

class ProjectCardFactory
{
	public:
		ProjectCardFactory() = delete;
		static ProjectCard	create(
			ProjectManager		&pm,
			RessourceManager	&rm,
			const std::string	&id,
			RendererSDL			&renderer
		);
}

#endif