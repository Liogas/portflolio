#include "ProjectCardFactory.hpp"

ProjectCard	ProjectCardFactory::create(
	ProjectManager		&pm,
	RessourceManager	&rm,
	const std::string	&id,
	RendererSDL			&renderer
)
{
	ProjectCard c;
	auto &projet = pm.get(id);
	TTF_Font *titleFont = rm.getFont(UIStyle::Body.path, UIStyle::Body.size);
	SDL_Color white{255,255,255,255};
	SDL_Surface *s = TTF_RenderUTF8_Blended(
		titleFont,
		projet.title.c_str(),
		white
	);
	c.titleTex = SDL_CreateTextureFromSurface(renderer.getRenderer(), s);
	c.titleRect = { 0, 0, s->w, s->h };
	SDL_FreeSurface(s);
	return (c);
}