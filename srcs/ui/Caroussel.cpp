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
    this->_lastSelectedCard = -1;
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

void    Caroussel::update(float deltaTime, RendererSDL &renderer, RessourceManager &rm)
{
    this->updatePagination(renderer, rm);
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
    {
        SDL_RenderSetClipRect(renderer.getRenderer(), &this->_rect);
        this->_cards[(this->_selectedCard - 1 + this->_cards.size()) % this->_cards.size()].draw(renderer);
        this->_cards[(this->_selectedCard + 1) % this->_cards.size()].draw(renderer);
        this->_cards[this->_selectedCard].draw(renderer);
        SDL_RenderSetClipRect(renderer.getRenderer(), nullptr);
    }
    this->drawPagination(renderer);
}

void    Caroussel::updatePagination(RendererSDL &renderer, RessourceManager &rm)
{
    if (this->_selectedCard == this->_lastSelectedCard)
        return ;
    std::stringstream   ss;
    ss  << std::setw(2)
        << std::setfill('0')
        << (this->_selectedCard + 1)
        << " / "
        << std::setw(2)
        << std::setfill('0')
        << this->_cards.size();
    std::string text = ss.str();
    this->_pagination.setText(
        text,
        renderer,
        rm.getFont(
			std::string(UIStyle::Font::KGSolid12.path),
			UIStyle::Font::KGSolid12.size
		),
        {255,255,255,255}
    );
    this->_lastSelectedCard = this->_selectedCard;
}

void    Caroussel::drawPagination(RendererSDL &renderer)
{
    this->_pagination.rect.x = this->_rect.x + this->_rect.w / 2 - this->_pagination.rect.w / 2;
    this->_pagination.rect.y = this->_rect.y + this->_rect.h - this->_pagination.rect.h * 2;
    this->_pagination.draw(renderer);
}

void Caroussel::drawAnimation(RendererSDL& renderer)
{
    float t    = this->_animation.progress / this->_animation.duration;
    int   dir  = this->_animation.direction;
    int   size = (int)this->_cards.size();

    int w = UIStyle::applyPercentage(UIStyle::Caroussel::MainWidth, this->_rect.w);
    int h = UIStyle::applyPercentage(UIStyle::Caroussel::MainHeight, this->_rect.h);
    int spacing = UIStyle::applyPercentage(UIStyle::Caroussel::Spacing, this->_rect.w);
    int cx = this->_rect.x + this->_rect.w / 2;
    int cy = this->_rect.y + this->_rect.h / 2;
    int step = w + spacing;

    SDL_Rect farLeftRect  = { cx - w / 2 - 2 * step, cy - h / 2, w, h };
    SDL_Rect leftRect     = { cx - w / 2 - step,      cy - h / 2, w, h };
    SDL_Rect centerRect   = { cx - w / 2,             cy - h / 2, w, h };
    SDL_Rect rightRect    = { cx - w / 2 + step,      cy - h / 2, w, h };
    SDL_Rect farRightRect = { cx - w / 2 + 2 * step,  cy - h / 2, w, h };

    auto wrap = [size](int i) { return (((i % size) + size) % size); };

    int oldSelected = this->_selectedCard;
    int newSelected = wrap(oldSelected + dir);
    int oldLeftIdx  = wrap(oldSelected - 1);
    int oldRightIdx = wrap(oldSelected + 1);
    int newLeftIdx  = wrap(newSelected - 1);
    int newRightIdx = wrap(newSelected + 1);

    auto lerpI = [](int a, int b, float u) { return (a + static_cast<int>((b - a) * u)); };
    auto animateRect = [&](SDL_Rect from, SDL_Rect to, float u)
    {
        return (SDL_Rect{ lerpI(from.x, to.x, u), lerpI(from.y, to.y, u), lerpI(from.w, to.w, u), lerpI(from.h, to.h, u) });
    };

    std::vector<int> drawOrder;
    auto place = [&](int idx, SDL_Rect rect, float depthT, int side)
    {
        ProjectCard &card = this->_cards[idx];
        card.rect = rect;
        card.depthT = depthT;
        card.side = side;
        drawOrder.push_back(idx);
    };

    if (dir > 0) // fleche droite : tout glisse vers la gauche, du neuf entre a droite
    {
        place(oldSelected, animateRect(centerRect, leftRect, t),  t,       -1);
        place(oldRightIdx, animateRect(rightRect, centerRect, t), 1.f - t, +1);

        if (oldLeftIdx == newRightIdx) // exactement 3 cartes : sort a gauche puis revient a droite
        {
            if (t < 0.5f)
                place(oldLeftIdx, animateRect(leftRect, farLeftRect, t * 2.f), 1.f, -1);
            else
                place(oldLeftIdx, animateRect(farRightRect, rightRect, (t - 0.5f) * 2.f), 1.f, +1);
        }
        else
        {
            place(oldLeftIdx,  animateRect(leftRect, farLeftRect, t),   1.f, -1);
            place(newRightIdx, animateRect(farRightRect, rightRect, t), 1.f, +1);
        }
    }
    else // fleche gauche : tout glisse vers la droite, du neuf entre a gauche
    {
        place(oldSelected, animateRect(centerRect, rightRect, t), t,       +1);
        place(oldLeftIdx,  animateRect(leftRect, centerRect, t),  1.f - t, -1);

        if (oldRightIdx == newLeftIdx)
        {
            if (t < 0.5f)
                place(oldRightIdx, animateRect(rightRect, farRightRect, t * 2.f), 1.f, +1);
            else
                place(oldRightIdx, animateRect(farLeftRect, leftRect, (t - 0.5f) * 2.f), 1.f, -1);
        }
        else
        {
            place(oldRightIdx, animateRect(rightRect, farRightRect, t), 1.f, +1);
            place(newLeftIdx,  animateRect(farLeftRect, leftRect, t),   1.f, -1);
        }
    }

    std::sort(drawOrder.begin(), drawOrder.end(), [&](int a, int b) { return (this->_cards[a].depthT > this->_cards[b].depthT); });
    for (int idx : drawOrder)
    {
        SDL_RenderSetClipRect(renderer.getRenderer(), &this->_rect);
        this->_cards[idx].draw(renderer);
        SDL_RenderSetClipRect(renderer.getRenderer(), nullptr);
    }
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

void    Caroussel::web()
{
    try
    {
        this->_cards[this->_selectedCard].open();
    } catch (const std::exception &e)
    {
        std::cerr << "ERROR Caroussel::web" << std::endl;
        throw (std::runtime_error(e.what()));
    }
}
