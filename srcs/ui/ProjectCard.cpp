#include "ProjectCard.hpp"

void	ProjectCard::update(RendererSDL &renderer)
{
	if (!this->dirty)
		return ;
	this->rebuild(renderer);
	this->dirty = false;
}

void	ProjectCard::rebuild(RendererSDL &renderer)
{
	auto *r = renderer.getRenderer();
	if (!this->texture)
	{
		this->texture = SDL_CreateTexture(
			r,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			
		)
	}
}

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