#include "ProjectCardFactory.hpp"

ProjectCard	ProjectCardFactory::create(
	const ProjectManager	&pm,
	RessourceManager		&rm,
	const std::string		&id,
	RendererSDL				&renderer
)
{
	ProjectCard c;
	auto &p = pm.get(id);
	// TITLE
	TTF_Font *titleFont = rm.getFont(std::string(UIStyle::Body.path), UIStyle::Body.size);
	SDL_Color white{255,255,255,255};
	SDL_Surface *s = TTF_RenderUTF8_Blended(
		titleFont,
		p.title.c_str(),
		white
	);
	c.titleTex = SDL_CreateTextureFromSurface(renderer.getRenderer(), s);
	c.titleRect = { 
		0, 
		0, 
		s->w,
		s->h 
	};
	c.titleSize = { s->w, s->h };
	SDL_FreeSurface(s);
	return (c);
}