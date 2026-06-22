#include "Caroussel.hpp"

namespace
{
    constexpr float kPi = 3.14159265358979323846f;

    inline float easeInOutQuad(float t)
    {
        return (t * t * (3.f - 2.f * t));
    }

    inline float lerpf2(float a, float b, float t)
    {
        return (a + (b - a) * t);
    }

    // distance signee la plus courte entre a et b sur un cercle de n positions
    inline float circularDiff(float a, float b, float n)
    {
        float d = a - b;
        d -= n * std::round(d / n);
        return (d);
    }
}

void    Caroussel::placeCardAtDiff(ProjectCard &card, float diff, int n)
{
    float anglePerSlot = 2.f * kPi / (float)n * UIStyle::Caroussel::AngleSpread;

    card.theta      = diff * anglePerSlot;
    card.originX    = this->_rect.x + this->_rect.w / 2.f;
    card.originY    = this->_rect.y + this->_rect.h / 2.f;
    card.ringRadius = (float)UIStyle::applyPercentage(UIStyle::Caroussel::RingRadiusRatio, this->_rect.w);
    card.focal      = (float)UIStyle::applyPercentage(UIStyle::Caroussel::FocalLengthRatio, this->_rect.w);
}

void    Caroussel::drawRing(RendererSDL &renderer, float phase)
{
    int n = (int)this->_cards.size();
    if (n == 0)
        return ;

    std::vector<int> order(n);
    for (int i = 0; i < n; ++i)
    {
        float diff = circularDiff((float)i, phase, (float)n);
        this->placeCardAtDiff(this->_cards[i], diff, n);
        order[i] = i;
    }
    std::sort(order.begin(), order.end(), [&](int a, int b)
    {
        float za = this->_cards[a].ringRadius * (1.f - cosf(this->_cards[a].theta));
        float zb = this->_cards[b].ringRadius * (1.f - cosf(this->_cards[b].theta));
        return (za > zb); // les plus loin (Z grand) dessinees en premier
    });

    SDL_RenderSetClipRect(renderer.getRenderer(), &this->_rect);
    for (int idx : order)
        this->_cards[idx].draw(renderer);
    SDL_RenderSetClipRect(renderer.getRenderer(), nullptr);
}

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
        container.y + UIStyle::applyPercentage(UIStyle::Computer::Title::Height, container.h) + UIStyle::applyPercentage(UIStyle::Computer::Spacing, container.h),
        container.w,
        UIStyle::applyPercentage(UIStyle::Caroussel::Height, container.h)
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

void    Caroussel::scrollUp()
{
    if (!this->_animation.on)
        this->_cards[this->_selectedCard].scroll(-30);
}

void    Caroussel::scrollDown()
{
    if (!this->_animation.on)
        this->_cards[this->_selectedCard].scroll(30);
}

void    Caroussel::update(float deltaTime, RendererSDL &renderer, RessourceManager &rm)
{
    this->updatePagination(renderer, rm);
    this->_cards[this->_selectedCard].update(renderer, rm, this->_rect);
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
    float phase;
    if (this->_animation.on)
    {
        float t  = this->_animation.progress / this->_animation.duration;
        float te = easeInOutQuad(t);
        phase = lerpf2((float)this->_selectedCard, (float)this->_selectedCard + this->_animation.direction, te);
    }
    else
        phase = (float)this->_selectedCard;

    this->drawRing(renderer, phase);
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
            UIStyle::Caroussel::Pagination::Font,
            UIStyle::Caroussel::Pagination::Size
		),
        UIStyle::Caroussel::Pagination::Color
    );
    this->_lastSelectedCard = this->_selectedCard;
}

void    Caroussel::drawPagination(RendererSDL &renderer)
{
    this->_pagination.rect.x = this->_rect.x + this->_rect.w / 2 - this->_pagination.rect.w / 2;
    this->_pagination.rect.y = this->_rect.y + this->_rect.h - this->_pagination.rect.h * 2;
    this->_pagination.draw(renderer);
}

void    Caroussel::layout()
{
    int n = (int)this->_cards.size();
    for (int i = 0; i < n; ++i)
    {
        this->_cards[i].scrollY = 0;
        float diff = circularDiff((float)i, (float)this->_selectedCard, (float)n);
        this->placeCardAtDiff(this->_cards[i], diff, n);
    }
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
