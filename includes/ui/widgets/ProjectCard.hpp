#ifndef PROJECTCARD_HPP
# define PROJECTCARD_HPP

#ifdef _WIN32
	#include <windows.h>
	#include <shellapi.h>
#else
	#include <unistd.h>
#endif

# include "Project.hpp"
# include "RessourceManager.hpp"

# include "UIStyle.hpp"
# include "UIText.hpp"

struct CardQuad
{
	SDL_FPoint	tl, tr, bl, br;
};

class ProjectCard
{
	public:
		ProjectCard(
			const Project 		*p,
			RendererSDL			&renderer,
			RessourceManager	&rm,
			SDL_Rect			&container
		);
		~ProjectCard();
		ProjectCard(ProjectCard&&) noexcept;
		ProjectCard& operator=(ProjectCard&&) noexcept;
		ProjectCard(const ProjectCard&) = delete;
		ProjectCard& operator=(const ProjectCard&) = delete;
		void	update(
			RendererSDL 		&renderer,
			RessourceManager 	&rm,
			SDL_Rect			&container
		);
		void	rebuild(
			RendererSDL 		&renderer,
			RessourceManager	&rm,
			SDL_Rect			&container
		);
		void	buildContainer(RendererSDL &renderer);
		void	buildTitle(
			RendererSDL 		&r,
			RessourceManager	&rm,
			int					containerW,
			int					containerH
		);
		void	buildDescription(
			RendererSDL 		&r,
			RessourceManager 	&rm,
			int					containerW,
			int					containerH
		);
		void	open();
		// void	buildTags(RendererSDL &r);
		void	draw(RendererSDL &renderer);
		// PROPS
		const Project		*project;
		SDL_Texture			*texture;
		SDL_Rect			rect;
		int					side;
		float				depthT;
		bool				dirty;
	private :
		void    buildCoverflowMesh(
			int                         centerX,
			int                         centerY,
			std::vector<SDL_Vertex>    &vertices,
			std::vector<int>           &indices
		) const;
};

# endif