#ifndef PROJECTCARD_HPP
# define PROJECTCARD_HPP

# include "Project.hpp"
# include "UIStyle.hpp"

# include "UIContainer.hpp"
# include "UIText.hpp"

class ProjectCard : public UIContainer
{
	public:
		UIText	title;
		UIText	description;
		void	draw(RendererSDL &renderer) override;
		void	init();
};

# endif