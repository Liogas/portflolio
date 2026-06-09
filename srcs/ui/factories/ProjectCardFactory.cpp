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
	c.description.setWrapWidth(150); // VALEUR BRUT A CHANGER
	c.title.setText(
		p.title,
		renderer,
		rm.getFont(std::string(UIStyle::KGSketch18.path), UIStyle::KGSketch18.size),
		UIStyle::Card::titleColor
	);
	c.description.setText(
		p.description,
		renderer,
		rm.getFont(std::string(UIStyle::KGSolid8.path), UIStyle::KGSolid8.size),
		UIStyle::Card::titleColor
	);
	return (c);
}