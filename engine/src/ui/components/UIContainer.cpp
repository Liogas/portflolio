#include "UIContainer.hpp"

void	UIContainer::setLayout(LayoutType l)
{
	this->_layout = l;
}

void	UIContainer::draw(RendererSDL &r)
{
	for (auto *child : this->_children)
		child->draw(r);
}

void	UIContainer::add(UIElement *e)
{
	this->_children.push_back(e);
	this->updateLayout();
}

void	UIContainer::setPadding(int p)
{
	this->_padding = p;
}

void	UIContainer::setSpacing(int s)
{
	this->_spacing = s;
}

void	UIContainer::updateLayout()
{
	if (this->_layout == LayoutType::Horizontal)
		this->layoutHorizontal();
	else if (this->_layout == LayoutType::Vertical)
		this->layoutVertical();
	else
		throw (std::runtime_error("ERROR UIContainer::updateLayout -> unknown layout"));
}

void	UIContainer::layoutHorizontal()
{
	int	currentX = this->rect.x + this->_padding;
	for (auto *child : this->_children)
	{
		child->rect.x = currentX;
		child->rect.y = this->rect.y + this->_padding;
		currentX += child->rect.w + this->_spacing;
	}
}

void	UIContainer::layoutVertical()
{
	int	currentY = this->rect.y + this->_padding;
	for (auto *child : this->_children)
	{
		child->rect.x = this->rect.x + this->_padding;
		child->rect.y = currentY;
		currentY += child->rect.h + this->_spacing;
	}
}