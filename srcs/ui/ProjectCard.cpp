#include "ProjectCard.hpp"

void	ProjectCard::draw(RendererSDL &renderer)
{
	auto *r = renderer.getRenderer();
	UIStyle::applyColor(r, UIStyle::Card::bkgColor);
	SDL_RenderFillRect(r, &this->rect);
	UIStyle::applyColor(r, UIStyle::Card::borderColor);
	SDL_RenderDrawRect(r, &this->rect);
	UIContainer::draw(renderer);
}

void	ProjectCard::init()
{
	this->setLayout(LayoutType::Vertical);
	this->setPadding(UIStyle::Card::Padding);
	this->setSpacing(UIStyle::Card::Spacing);
	this->add(&this->title);
	this->add(&this->description);
}