#include "Caroussel.hpp"

void    Caroussel::init(
    std::vector<std::string>	projectIds,
    const SDL_Rect				&container,
    RessourceManager			&rm,
    const ProjectManager		&pm,
    RendererSDL					&renderer
)
{
    this->_rect = {
        container.x,
        container.y + static_cast<int>(container.y * 0.2f),
        container.w,
        static_cast<int>(container.h * 0.8f)
    };
    this->_visibleCards = 3;
    this->_spacing = 20;
    this->_selectedCard = 1;
    c.cards.reserve(projectIds.size());
    for (auto &p : projectIds)
    {
        this->_cards.push_back(ProjectCardFactory::create(
            pm,
            rm,
            p,
            renderer
        ));
        this->_cards.back().init();
    }
    this->layout();
}

void    Caroussel::nextCard()
{

}

void    Caroussel::previousCard()
{

}

void    Caroussel::draw()
{

}

void    Caroussel::layout()
{

}

void layoutCaroussel(Caroussel &c)
{
    int spacing = c.spacing;
    int visible = c.visibleCards;
    int cardW = (c.rect.w - spacing * (visible + 1)) / visible;
    int cardH = c.rect.h - spacing * 2;
    int cardW2 = cardW * 0.8f;
    int cardH2 = cardH * 0.8f;

    int start = c.selectedCard - 1;
    if (start < 0)
        start = c.cards.size() - 1;

    for (int i = 0; i < c.visibleCards; i++)
    {
        ProjectCard &card = c.cards[start];
        int w = cardW, h = cardH;
        if (i != 1)
        {
            w = cardW2;
            h = cardH2;
        }
        card.rect = {
            c.rect.x + spacing + i * (cardW + spacing),
            c.rect.y + spacing,
            w,
            h
        };
        card.updateLayout();
        start++;
        if (start == (int)c.cards.size())
            start = 0;
    }
}

void    drawCaroussel(RendererSDL &renderer, Caroussel &c)
{
    int start = c.selectedCard - 1;
        if (start < 0)
            start = c.cards.size() - 1;
    for (int i = 0; i < c.visibleCards; ++i)
    {
        c.cards[start].draw(renderer);
        start++;
        if (start >= (int)c.cards.size())
            start = 0;
    }
}

void    nextProject(Caroussel &c)
{
    c.selectedCard += 1;
	if (c.selectedCard >= (int)c.cards.size())
		c.selectedCard = 0;
    layoutCaroussel(c);
}

void    previousProject(Caroussel &c)
{
    c.selectedCard -= 1;
    if (c.selectedCard < 0)
        c.selectedCard = c.cards.size();
    layoutCaroussel(c);
}
