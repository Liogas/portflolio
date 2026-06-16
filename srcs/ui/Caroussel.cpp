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
        container.y + UIStyle::applyPercentage(UIStyle::Computer::TitleHeight, container.h) + UIStyle::applyPercentage(UIStyle::Computer::Spacing, container.h),
        container.w,
        UIStyle::applyPercentage(UIStyle::Computer::CarousselHeight, container.h)
    };
    this->_visibleCard = 3;
    this->_spacing = UIStyle::Caroussel::Spacing;
    this->_selectedCard = 1;
    this->_cards.reserve(projectIds.size());
    for (auto &id : projectIds)
    {
	    auto &p = pm.get(id);
        ProjectCard card(&p, renderer, rm, this->_rect);
        this->_cards.push_back(std::move(card));
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
    SDL_SetRenderDrawColor(renderer.getRenderer(), 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer.getRenderer(), &this->_rect);
    if (this->_animation.on)
        this->drawAnimation(renderer);
    else
    {
        this->_cards[(this->_selectedCard - 1 + this->_cards.size()) % this->_cards.size()].draw(renderer);
        this->_cards[(this->_selectedCard + 1) % this->_cards.size()].draw(renderer);
        this->_cards[this->_selectedCard].draw(renderer);
    }
}

void Caroussel::drawAnimation(RendererSDL& renderer)
{
    float t = this->_animation.progress / this->_animation.duration;

    int w = UIStyle::applyPercentage(UIStyle::Caroussel::MainWidth, this->_rect.w);
    int h = UIStyle::applyPercentage(UIStyle::Caroussel::MainHeight, this->_rect.h);
    int spacing = UIStyle::applyPercentage(UIStyle::Caroussel::Spacing, this->_rect.w);
    int cx = this->_rect.x + this->_rect.w / 2;
    int cy = this->_rect.y + this->_rect.h / 2;

    SDL_Rect leftRect   = { cx - w / 2 - spacing - w, cy - h / 2, w, h };
    SDL_Rect centerRect = { cx - w / 2,               cy - h / 2, w, h };
    SDL_Rect rightRect  = { cx - w / 2 + w + spacing, cy - h / 2, w, h };

    int size = this->_cards.size();
    ProjectCard &prev   = this->_cards[(this->_selectedCard - 1 + size) % size];
    ProjectCard &center = this->_cards[this->_selectedCard];
    ProjectCard &next   = this->_cards[(this->_selectedCard + 1) % size];

    auto lerp = [](int a, int b, float t) { return (a + static_cast<int>((b - a) * t)); };
    auto animateRect = [&](SDL_Rect from, SDL_Rect to, float t)
    {
        return (SDL_Rect{ lerp(from.x, to.x, t), lerp(from.y, to.y, t), lerp(from.w, to.w, t), lerp(from.h, to.h, t) });
    };

    if (this->_animation.direction > 0)
    {
        prev.rect = animateRect(leftRect, centerRect, t);
        prev.depthT = 1.f - t;
        prev.side = -1;

        center.rect = animateRect(centerRect, rightRect, t);
        center.depthT = t;
        center.side = +1;

        next.rect = animateRect(rightRect, rightRect, t);
        next.depthT = 1.f;
        next.side = +1;
    }
    else
    {
        prev.rect = animateRect(leftRect, leftRect, t);
        prev.depthT = 1.f;
        prev.side = -1;

        center.rect = animateRect(centerRect, leftRect, t);
        center.depthT = t;
        center.side = -1;

        next.rect = animateRect(rightRect, centerRect, t);
        next.depthT = 1.f - t;
        next.side = +1;
    }

    ProjectCard *order[3] = { &prev, &center, &next };
    std::sort(order, order + 3, [](const ProjectCard *a, const ProjectCard *b) { return (a->depthT > b->depthT); });
    for (auto *c : order)
        c->draw(renderer);
}

void    Caroussel::layout()
{
    int spacing = UIStyle::applyPercentage(UIStyle::Caroussel::Spacing, this->_rect.w);
    int w = UIStyle::applyPercentage(UIStyle::Caroussel::MainWidth, this->_rect.w);
    int h = UIStyle::applyPercentage(UIStyle::Caroussel::MainHeight, this->_rect.h);
    int cx = this->_rect.x + this->_rect.w / 2;
    int cy = this->_rect.y + this->_rect.h / 2;
    
    ProjectCard &card = this->_cards[this->_selectedCard];
    ProjectCard &left = this->_cards[(this->_selectedCard - 1 + this->_cards.size()) % this->_cards.size()];
    ProjectCard &right = this->_cards[(this->_selectedCard + 1) % this->_cards.size()];
    card.rect = {
        cx - w / 2,
        cy - h / 2,
        w,
        h
    };
    card.depthT = 0.0;
    card.side = 0;
    left.rect = {
        card.rect.x - spacing - w,
        card.rect.y,
        w,
        h
    };
    left.depthT = 1.f;
    left.side = -1;
    right.rect = {
        card.rect.x + w + spacing,
        card.rect.y,
        w,
        h
    };
    right.depthT = 1.f;
    right.side = +1;
}
