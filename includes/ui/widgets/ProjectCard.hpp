#ifndef PROJECTCARD_HPP
# define PROJECTCARD_HPP

# include "Project.hpp"

# include "UIStyle.hpp"
# include "UIText.hpp"

class ProjectCard
{
	public:
		Project		*project;
		SDL_Texture	*texture;
		bool		dirty;
		void	update();
		void	rebuild();
		void	draw(RendererSDL &renderer);
};

# endif