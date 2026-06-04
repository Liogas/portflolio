#include "ComputerUIFactory.hpp"

ComputerUI	ComputerUIFactory::create(
	const ComputerData		&data,
	const ProjectManager	&pm,
	RessourceManager		&rm,
	const RendererSDL		&renderer
)
{
	(void)pm;
	ComputerUI ui;
	ui.rect = { 
		renderer.getWidth() / 4,
    	10,
   	 	renderer.getWidth() / 2,
    	renderer.getHeight() - 20
	};
	ui.titleBar = TitleBarFactory::create(data.title, ui.rect, rm, renderer);
	ui.caroussel = CarousselFactory::create(data.projectIds, ui.rect, rm, pm, renderer);
	return (ui);
}