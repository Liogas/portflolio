#ifndef CAROUSSEL_HPP
# define CAROUSSEL_HPP

# include "ProjectCard.hpp"
# include "UIStyle.hpp"
# include <vector>

class Caroussel
{
	public :
		void	init(
			std::vector<std::string>	projectIds,
			const SDL_Rect				&container,
			RessourceManager			&rm,
			const ProjectManager		&pm,
			RendererSDL					&renderer
		)
		void	nextCard();
		void	previousCard()
		void	draw();
		void	layout();
	private :
		std::vector<ProjectCard>	_cards;
		int							_selectedCard;
		int							_visibleCard;
		SDL_Rect					_rect;
};

void	layoutCaroussel(Caroussel &c);
void	drawCaroussel(RendererSDL &renderer, Caroussel &c);
void	nextProject(Caroussel &c);
void	previousProject(Caroussel &c);

# endif