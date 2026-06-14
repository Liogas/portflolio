#include "ComputerUIFactory.hpp"

ComputerUI	ComputerUIFactory::create(
	const ComputerData		&data,
	const ProjectManager	&pm,
	RessourceManager		&rm,
	RendererSDL		&renderer
)
{
	ComputerUI ui;
	ui.rect = {
		UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getWidth()),
    	UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getHeight()),
   	 	renderer.getWidth() - UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getWidth()),
    	renderer.getHeight() - UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getHeight())
	};
	ui.title.setText(
		data.title,
		renderer,
		rm.getFont(std::string(UIStyle::WC55.path), UIStyle::WC55.size),
		UIStyle::Card::titleColor
	);
	ui.title.rect.x = ui.rect.x + (ui.rect.w - ui.title.rect.w) / 2;
	ui.caroussel.init(data.projectIds, ui.rect, rm, pm, renderer);
	return (ui);
}