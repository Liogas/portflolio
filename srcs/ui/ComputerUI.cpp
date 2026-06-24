#include "ComputerUI.hpp"

ComputerUI::ComputerUI(
	const std::string		&id,
	ComputerManager			&cm,
	RessourceManager		&rm,
    const ProjectManager	&pm,
    RendererSDL				&renderer
):
	_data(cm.get(id)),
	_rm(rm),
	_renderer(renderer)
{
    this->_id = id;
	this->_closeRequested = false;
	this->_rect = {
		UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getWidth()),
    	UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getHeight()),
   	 	renderer.getWidth() - UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getWidth()) * 2,
    	renderer.getHeight() - UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getHeight()) * 2
	};
	this->_title.setText(
		this->_data.title,
		renderer,
		rm.getFont(
			UIStyle::Computer::Title::Font,
			UIStyle::Computer::Title::Size
		),
		UIStyle::Computer::Title::Color
	);
	this->_title.rect.x = this->_rect.w / 2 - this->_title.rect.w / 2;
	this->_title.rect.y = this->_rect.y + UIStyle::applyPercentage(UIStyle::Computer::Spacing, renderer.getWidth());
	this->_caroussel.init(this->_data.projectIds, this->_rect, rm, pm, this->_renderer);
}

void    ComputerUI::update(float dt)
{
    this->_caroussel.update(dt, this->_renderer, this->_rm);
}

void    ComputerUI::handleInput(const InputSDL &input)
{
    if (input.isKeyPressed(SDL_SCANCODE_RIGHT))
		this->_caroussel.nextCard();
	else if (input.isKeyPressed(SDL_SCANCODE_LEFT))
		this->_caroussel.previousCard();
	else if (input.isKeyPressed(SDL_SCANCODE_RETURN))
		this->_caroussel.web();
	else if (input.isKeyPressed(SDL_SCANCODE_UP))
		this->_caroussel.scrollUp();
	else if (input.isKeyPressed(SDL_SCANCODE_DOWN))
		this->_caroussel.scrollDown();
    else if (input.isKeyPressed(SDL_SCANCODE_ESCAPE))
        this->_closeRequested = true;
}

void    ComputerUI::render(RendererSDL &renderer)
{
    auto r = renderer.getRenderer();
	SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
	UIStyle::applyColor(r, UIStyle::Computer::BackgroundColor);
    SDL_RenderFillRect(
        r,
        &this->_rect
    );
	UIStyle::applyColor(r, UIStyle::Computer::BorderColor);
    SDL_RenderDrawRect(
        r,
        &this->_rect
    );
	this->_title.draw(renderer);
    this->_caroussel.draw(renderer);
}

bool    ComputerUI::blocksGameplay() const
{
    return (true);
}

bool    ComputerUI::shouldClose() const
{
    return (this->_closeRequested);
}
