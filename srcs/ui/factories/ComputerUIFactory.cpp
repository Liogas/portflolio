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
			std::string(UIStyle::Font::WC55.path),
			UIStyle::Font::WC55.size
		),
		UIStyle::Card::TitleColor
	);
	ui.title.rect.x = ui.rect.w / 2 - ui.title.rect.w / 2;
	ui.title.rect.y = ui.rect.y + UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getWidth());
	ui.caroussel.init(data.projectIds, ui.rect, rm, pm, renderer);
	return (ui);
}