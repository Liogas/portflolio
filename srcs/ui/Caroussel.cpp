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
        card.titleRect = {
            card.rect.x + (card.rect.w - card.titleRect.w) / 2,
            card.rect.y + 10,
            card.titleSize.x,
            card.titleSize.y,
        };
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
        drawProjectCard(renderer, c.cards[start]);
        start++;
        if (start >= (int)c.cards.size())
            start = 0;
    }
}

void    destroyCaroussel(Caroussel &c)
{
    for (auto &card : c.cards)
        destroyProjectCard(card);
}