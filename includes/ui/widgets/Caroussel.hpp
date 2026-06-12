#ifndef CAROUSSEL_HPP
# define CAROUSSEL_HPP

# include "ProjectCard.hpp"
# include "UIStyle.hpp"
# include <vector>

# include "RessourceManager.hpp"
# include "ProjectManager.hpp"
# include "ProjectCardFactory.hpp"

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
		void	draw(RendererSDL &renderer);
		void	drawAnimation(RendererSDL &renderer);
		void	layout();
		void	update(float deltaTime);
	private :
		std::vector<ProjectCard>	_cards;
		int							_selectedCard;
		int							_visibleCard;
		SDL_Rect					_rect;
		int							_spacing;
		CarousselAnimation			_animation;
};

# endif