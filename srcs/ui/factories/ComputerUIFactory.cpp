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
   	 	renderer.getWidth() - UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getWidth()) * 2,
    	renderer.getHeight() - UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getHeight()) * 2
	};
	ui.title.setText(
		data.title,
		renderer,
		rm.getFont(
			UIStyle::Computer::Title::Font,
			UIStyle::Computer::Title::Size
		),
		UIStyle::Computer::Title::Color
	);
	ui.title.rect.x = ui.rect.w / 2 - ui.title.rect.w / 2;
	ui.title.rect.y = ui.rect.y + UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getWidth());
	ui.caroussel.init(data.projectIds, ui.rect, rm, pm, renderer);
	return (ui);
}