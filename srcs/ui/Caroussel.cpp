#include "Caroussel.hpp"

void layoutCaroussel(Caroussel &c)
{
    int spacing = c.spacing;
    int visible = c.visibleCards;
    int cardW = (c.rect.w - spacing * (visible + 1)) / visible;
    int cardH = c.rect.h - spacing * 2;

    int start = c.selectedCard - 1;
    if (start < 0)
        start = c.cards.size() - 1;

    for (int i = 0; i < c.visibleCards; i++)
    {
        ProjectCard &card = c.cards[start];
        card.rect = {
            c.rect.x + spacing + i * (cardW + spacing),
            c.rect.y + spacing,
            cardW,
            cardH
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
