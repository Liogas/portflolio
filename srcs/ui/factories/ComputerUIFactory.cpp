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
		10,
    	10,
   	 	renderer.getWidth() - 20,
    	renderer.getHeight() - 20
	};
	ui.title.setText(
		data.title,
		renderer,
		rm.getFont(std::string(UIStyle::WC55.path), UIStyle::WC55.size),
		UIStyle::Card::titleColor
	);
	ui.title.rect.x = ui.rect.x + (ui.rect.w - ui.title.rect.w) / 2;
	ui.title.rect.y = ui.rect.y + 20;
	ui.caroussel = CarousselFactory::create(data.projectIds, ui.rect, rm, pm, renderer);
	return (ui);
}