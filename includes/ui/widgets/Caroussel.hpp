#ifndef CAROUSSEL_HPP
# define CAROUSSEL_HPP

# include "ProjectCard.hpp"
# include "UIStyle.hpp"
# include <vector>

# include "RessourceManager.hpp"
# include "ProjectManager.hpp"

struct CarousselAnimation
{
	bool	on;
	float	progress;
	float	duration;
	int		direction;
};

class Caroussel
{
	public :
		void	init(
			std::vector<std::string>	projectIds,
			const SDL_Rect				&container,
			RessourceManager			&rm,
			const ProjectManager		&pm,
			RendererSDL					&renderer
		);
		void	nextCard();
		void	previousCard();
		void	scrollUp();
		void	scrollDown();
		void	draw(RendererSDL &renderer);
		void	drawPagination(RendererSDL &renderer);
		void	web();
		void	layout();
		void	update(float deltaTime, RendererSDL &renderer, RessourceManager &rm);
		void	updatePagination(RendererSDL &renderer, RessourceManager &rm);
	private :
		std::vector<ProjectCard>	_cards;
		int							_selectedCard;
		int							_lastSelectedCard;
		UIText						_pagination;
		int							_visibleCard;
		SDL_Rect					_rect;
		int							_spacing;
		CarousselAnimation			_animation;
		void    placeCardAtDiff(ProjectCard &card, float diff, int n);
		void    drawRing(RendererSDL &renderer, float phase);
};

# endif