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
        container.y + static_cast<int>(container.h * 0.2f),
        container.w,
        static_cast<int>(container.h * 0.8f)
    };
    this->_visibleCard = 3;
    this->_spacing = 20;
    this->_selectedCard = 1;
    this->_cards.reserve(projectIds.size());
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
    this->_animation.on = false;
    this->_animation.duration = 0.3f;
    this->_animation.progress = 0.f;
    this->_animation.direction = 0;
    this->layout();
}

void    Caroussel::nextCard()
{
    if (this->_animation.on)
        return ;
    this->_animation.on = true;
    this->_animation.direction = 1;
    this->_animation.progress = 0.f;
}

void    Caroussel::previousCard()
{
    if (this->_animation.on)
        return ;
    this->_animation.on = true;
    this->_animation.direction = -1;
    this->_animation.progress = 0.f;
}

void    Caroussel::update(float deltaTime)
{
    if (!this->_animation.on)
        return ;
    this->_animation.progress += deltaTime;
    if (this->_animation.progress >= this->_animation.duration)
    {
        this->_animation.progress = this->_animation.duration;
        this->_selectedCard += this->_animation.direction;
        if (this->_selectedCard >= (int)this->_cards.size())
            this->_selectedCard = 0;
        if (this->_selectedCard < 0)
            this->_selectedCard = this->_cards.size() - 1;
        this->layout();
        this->_animation.on = false;
    }
}

void    Caroussel::draw(RendererSDL &renderer)
{
    if (this->_animation.on)
        this->drawAnimation(renderer);
    else
        this->_cards[this->_selectedCard].draw(renderer);
    // int start = this->_selectedCard - 1;
    // if (start < 0)
    //     start = this->_cards.size() - 1;
    // for (int i = 0; i < this->_visibleCard; ++i)
    // {
    //     this->_cards[start].draw(renderer);
    //     start++;
    //     if (start >= (int)this->_cards.size())
    //         start = 0;
    // }
}

void Caroussel::drawAnimation(RendererSDL& renderer)
{
    float t = _animation.progress / _animation.duration;

    int centralW = _rect.w / 4;
    int centralH = _rect.h - _spacing * 2;

    int centerX = (_rect.w / 2) - centralW / 2;
    int centerY = _rect.y + (_rect.h / 2) - centralH / 2;

    int nextIndex =
        (this->_selectedCard + this->_animation.direction + this->_cards.size())
        % this->_cards.size();

    ProjectCard &current = this->_cards[this->_selectedCard];
    ProjectCard &next = this->_cards[nextIndex];

    int offset = static_cast<int>(t * centralW);

    current.rect =
    {
        centerX - offset * this->_animation.direction,
        centerY,
        centralW,
        centralH
    };

    next.rect =
    {
        centerX + centralW * this->_animation.direction
            - offset * this->_animation.direction,
        centerY,
        centralW,
        centralH
    };

    current.updateLayout();
    next.updateLayout();

    current.draw(renderer);
    next.draw(renderer);
}

void    Caroussel::layout()
{
    int centralCardW = this->_rect.w / 4;
    int centralCardH = this->_rect.h - this->_spacing * 2;
    int centralCardX = (this->_rect.w / 2) - (centralCardW / 2);
    int centralCardY = this->_rect.y + (this->_rect.h / 2) - (centralCardH / 2);

    ProjectCard &card = this->_cards[this->_selectedCard];
    card.rect = {
        centralCardX,
        centralCardY,
        centralCardW,
        centralCardH
    };

    card.updateLayout();
    
    // int start = this->_selectedCard - 1;
    // if (start < 0)
    //     start = this->_cards.size() - 1;

    // for (int i = 0; i < this->_visibleCard; i++)
    // {
    //     ProjectCard &card = this->_cards[start];
    //     int w = centralCardW, h = cardH;
    //     if (i != 1)
    //     {
    //         w = cardW2;
    //         h = cardH2;
    //     }
    //     card.rect = {
    //         this->_rect.x + this->_spacing + i * (cardW + this->_spacing),
    //         this->_rect.y + this->_spacing,
    //         w,
    //         h
    //     };
    //     card.updateLayout();
    //     start++;
    //     if (start == (int)this->_cards.size())
    //         start = 0;
    // }
}

// void layoutCaroussel(Caroussel &c)
// {
//     int spacing = c.spacing;
//     int visible = c.visibleCards;
//     int cardW = (c.rect.w - spacing * (visible + 1)) / visible;
//     int cardH = c.rect.h - spacing * 2;
//     int cardW2 = cardW * 0.8f;
//     int cardH2 = cardH * 0.8f;

//     int start = c.selectedCard - 1;
//     if (start < 0)
//         start = c.cards.size() - 1;

//     for (int i = 0; i < c.visibleCards; i++)
//     {
//         ProjectCard &card = c.cards[start];
//         int w = cardW, h = cardH;
//         if (i != 1)
//         {
//             w = cardW2;
//             h = cardH2;
//         }
//         card.rect = {
//             c.rect.x + spacing + i * (cardW + spacing),
//             c.rect.y + spacing,
//             w,
//             h
//         };
//         card.updateLayout();
//         start++;
//         if (start == (int)c.cards.size())
//             start = 0;
//     }
// }

// void    drawCaroussel(RendererSDL &renderer, Caroussel &c)
// {
//     int start = c.selectedCard - 1;
//         if (start < 0)
//             start = c.cards.size() - 1;
//     for (int i = 0; i < c.visibleCards; ++i)
//     {
//         c.cards[start].draw(renderer);
//         start++;
//         if (start >= (int)c.cards.size())
//             start = 0;
//     }
// }

// void    nextProject(Caroussel &c)
// {
//     c.selectedCard += 1;
// 	if (c.selectedCard >= (int)c.cards.size())
// 		c.selectedCard = 0;
//     layoutCaroussel(c);
// }

// void    previousProject(Caroussel &c)
// {
//     c.selectedCard -= 1;
//     if (c.selectedCard < 0)
//         c.selectedCard = c.cards.size();
//     layoutCaroussel(c);
// }
