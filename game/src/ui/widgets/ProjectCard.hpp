#ifndef PROJECTCARD_HPP
# define PROJECTCARD_HPP

#ifdef _WIN32
	#include <windows.h>
	#include <shellapi.h>
#else
	#include <unistd.h>
#endif

# include "Project.hpp"
# include "resources/ResourceManager.hpp"

# include "UIStyle.hpp"
# include "UIText.hpp"

# include <algorithm>
# include <cmath>

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
			ResourceManager	&rm,
			SDL_Rect			&container
		);
		~ProjectCard();
		ProjectCard(ProjectCard&&) noexcept;
		ProjectCard& operator=(ProjectCard&&) noexcept;
		ProjectCard(const ProjectCard&) = delete;
		ProjectCard& operator=(const ProjectCard&) = delete;
		void	update(
			RendererSDL 		&renderer,
			ResourceManager 	&rm,
			SDL_Rect			&container
		);
		void	rebuild(
			RendererSDL 		&renderer,
			ResourceManager	&rm,
			SDL_Rect			&container
		);
		void	buildContainer(RendererSDL &renderer);
		void 	buildTitle(
			RendererSDL &r,
			ResourceManager &rm,
			int containerW,
			int containerH,
			int &cursorY
		);
		void 	buildDescription(
			RendererSDL &r,
			ResourceManager &rm,
			int containerW,
			int containerH,
			int &cursorY
		);
		void 	buildImage(
			ResourceManager &rm,
			int containerW,
			int containerH,
			int &cursorY
		);
		void 	buildTags(
			ResourceManager &rm,
			int containerW,
			int containerH,
			int &cursorY
		);
		void	open();
		void	draw(RendererSDL &renderer);
		void	scroll(int delta);
		// PROPS
		const Project	*project;
		SDL_Texture		*texture;
		SDL_Rect		rect;
		float   		theta;       // angle de rotation/position sur l'anneau, en radians (0 = face camera)
		float   		originX;     // centre du caroussel a l'ecran (X)
		float   		originY;     // centre du caroussel a l'ecran (Y)
		float   		ringRadius;  // rayon de l'anneau en pixels
		float  	 		focal;        // distance focale virtuelle en pixels
		bool			dirty;
		int				scrollY;
		int				contentH;
	private :
		void    buildCoverflowMesh(
			std::vector<SDL_Vertex>    &vertices,
			std::vector<int>           &indices
		) const;
};

# endif