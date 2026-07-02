#include "PauseMenuUI.hpp"

// Données statiques — facile à étendre plus tard
const std::vector<std::string> PauseMenuUI::_mainItems = {
    "Reprendre",
    "Options graphiques",
    "Controles",
    "Quitter"
};

const std::vector<std::pair<int,int>> PauseMenuUI::_resolutions = {
    { 1280,  720 },
    { 1600,  900 },
    { 1920, 1080 },
    { 2560, 1440 }
};


PauseMenuUI::PauseMenuUI(
    RendererSDL         &renderer,
    ResourceManager    &rm,
    entt::dispatcher    &dispatcher,
    ControlsConfig      &cfg
) :
    _renderer(renderer),
    _rm(rm),
    _dispatcher(dispatcher),
    _panel(Panel::MAIN),
    _selected(0),
    _closeRequested(false),
    _cfg(cfg),
    _rebindingAction(-1),
    _waitNextFrame(false),
    _scrollOffset(0)
{
    int w = UIStyle::applyPercentage(UIStyle::PauseMenu::WidthRatio,  renderer.getWidth());
    int h = UIStyle::applyPercentage(UIStyle::PauseMenu::HeightRatio, renderer.getHeight());
    this->_rect = {
        renderer.getWidth()  / 2 - w / 2,
        renderer.getHeight() / 2 - h / 2,
        w,
        h
    };
}

bool    PauseMenuUI::blocksGameplay() const { return true;  }
bool    PauseMenuUI::shouldClose()    const { return this->_closeRequested; }
void    PauseMenuUI::update(float)          {}

void    PauseMenuUI::handleInput(const InputSDL &input)
{
    if (this->_rebindingAction >= 0)
    {
        // Ignore le premier frame (celui ou ENTREE a ete presse pour entrer ici)
        if (this->_waitNextFrame)
        {
            this->_waitNextFrame = false;
            return ;
        }

        SDL_Scancode pressed = input.getLastPressedKey();
        if (pressed == SDL_SCANCODE_UNKNOWN)
            return ; // pas encore de touche pressee

        if (pressed == SDL_SCANCODE_ESCAPE)
        {
            // Annulation
            this->_rebindingAction = -1;
            return ;
        }

        // Verifie qu'on n'assigne pas une touche deja utilisee par une autre action
        for (int i = 0; i < (int)Action::COUNT; ++i)
        {
            if (i != this->_rebindingAction && this->_cfg.get((Action)i) == pressed)
            {
                // Echange les deux bindings
                SDL_Scancode old = this->_cfg.get((Action)this->_rebindingAction);
                this->_cfg.set((Action)i, old);
                break;
            }
        }
        this->_cfg.set((Action)this->_rebindingAction, pressed);
        this->_rebindingAction = -1;
        return ;
    }

    const int count =
        (_panel == Panel::MAIN)     ? (int)_mainItems.size()   :
        (_panel == Panel::GRAPHICS) ? (int)_resolutions.size() :
                                      (int)Action::COUNT;

    if (input.isKeyPressed(SDL_SCANCODE_UP))
    {
        this->_selected = (this->_selected - 1 + count) % count;
        this->updateScroll(count);
    }
    else if (input.isKeyPressed(SDL_SCANCODE_DOWN))
    {
        this->_selected = (this->_selected + 1) % count;
        this->updateScroll(count);
    }
    else if (input.isKeyPressed(SDL_SCANCODE_RETURN))
        this->confirm();
    else if (input.isKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        if (this->_panel != Panel::MAIN)
        {
            this->_panel    = Panel::MAIN;
            this->_selected = 0;
            this->_scrollOffset = 0;
        }
        else
            this->_closeRequested = true;
    }
}

void    PauseMenuUI::updateScroll(int count)
{
    int spacing      = UIStyle::applyPercentage(UIStyle::PauseMenu::Spacing, this->_rect.h);
    int titleAreaH   = UIStyle::PauseMenu::Title::Size + spacing * 4;
    int itemH        = UIStyle::PauseMenu::Item::Size + spacing + 4;
    int visibleCount = std::max(1, (this->_rect.h - titleAreaH) / itemH);

    if (this->_selected < this->_scrollOffset)
        this->_scrollOffset = this->_selected;
    else if (this->_selected >= this->_scrollOffset + visibleCount)
        this->_scrollOffset = this->_selected - visibleCount + 1;

    this->_scrollOffset = std::clamp(
        this->_scrollOffset, 0, std::max(0, count - visibleCount)
    );
}

void    PauseMenuUI::confirm()
{
    if (this->_panel == Panel::MAIN)
    {
        switch (this->_selected)
        {
            case 0: this->_closeRequested = true; break;
            case 1: 
                this->_panel = Panel::GRAPHICS;
                this->_selected = 0;
                this->_scrollOffset = 0;
                break;
            case 2:
                this->_panel = Panel::CONTROLS;
                this->_selected = 0;
                this->_scrollOffset = 0;
                break;
            case 3: this->_dispatcher.trigger(QuitGameEvent{}); break;
        }
    }
    else if (this->_panel == Panel::GRAPHICS)
    {
        if (this->_selected == 0)
            this->_dispatcher.trigger(ToggleFullScreenEvent{});
        else
        {
            auto [w, h] = this->_resolutions[this->_selected - 1];
            this->_dispatcher.trigger(ChangeResolutionEvent{ w, h });
        }
        this->_panel = Panel::MAIN; this->_selected = 0; this->_scrollOffset = 0;
    }
    else // CONTROLS
    {
        this->_rebindingAction = this->_selected;
        this->_waitNextFrame   = true;
    }
}

void    PauseMenuUI::renderPanel(
    RendererSDL                     &renderer,
    const std::string               &title,
    const std::vector<std::string>  &items
)
{
    auto *r   = renderer.getRenderer();
    int spacing = UIStyle::applyPercentage(UIStyle::PauseMenu::Spacing, this->_rect.h);

    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    UIStyle::applyColor(r, UIStyle::PauseMenu::BkgColor);
    SDL_RenderFillRect(r, &this->_rect);
    UIStyle::applyColor(r, UIStyle::PauseMenu::BorderColor);
    SDL_RenderDrawRect(r, &this->_rect);

    UIText t;
    t.setText(title, renderer,
        this->_rm.getFont(UIStyle::PauseMenu::Title::Font, UIStyle::PauseMenu::Title::Size),
        UIStyle::PauseMenu::BorderColor);
    t.rect.x = this->_rect.x + (this->_rect.w - t.rect.w) / 2;
    t.rect.y = this->_rect.y + spacing;
    t.draw(renderer);

    int cursorY = t.rect.y + t.rect.h + spacing * 2;
    UIStyle::applyColor(r, UIStyle::PauseMenu::BorderColor);
    SDL_RenderDrawLine(r,
        this->_rect.x + spacing, cursorY,
        this->_rect.x + this->_rect.w - spacing, cursorY);
    cursorY += spacing;

    // Calcul de la zone et du nombre visible
    int itemAreaTop  = cursorY;
    int itemH        = UIStyle::PauseMenu::Item::Size + spacing + 4;
    int itemAreaH    = this->_rect.y + this->_rect.h - spacing - itemAreaTop;
    int visibleCount = std::max(1, itemAreaH / itemH);
    int endIdx       = std::min((int)items.size(), this->_scrollOffset + visibleCount);

    // Clip strict sur la zone items
    SDL_Rect clip = { this->_rect.x + 1, itemAreaTop, this->_rect.w - 2, itemAreaH };
    SDL_RenderSetClipRect(r, &clip);

    // Indicateur haut
    if (this->_scrollOffset > 0)
    {
        UIText up;
        up.setText("^", renderer,
            this->_rm.getFont(UIStyle::PauseMenu::Item::Font, UIStyle::PauseMenu::Item::Size),
            UIStyle::PauseMenu::ItemColor);
        up.rect.x = this->_rect.x + (this->_rect.w - up.rect.w) / 2;
        up.rect.y = itemAreaTop;
        up.draw(renderer);
        cursorY += up.rect.h + spacing / 2;
    }

    for (int i = this->_scrollOffset; i < endIdx; ++i)
    {
        SDL_Color color = (i == this->_selected)
            ? UIStyle::PauseMenu::SelectedColor
            : UIStyle::PauseMenu::ItemColor;

        if (i == this->_selected)
        {
            UIText arrow;
            arrow.setText(">", renderer,
                this->_rm.getFont(UIStyle::PauseMenu::Item::Font, UIStyle::PauseMenu::Item::Size),
                color);
            arrow.rect.x = this->_rect.x + spacing;
            arrow.rect.y = cursorY;
            arrow.draw(renderer);
        }

        UIText item;
        item.setText(items[i], renderer,
            this->_rm.getFont(UIStyle::PauseMenu::Item::Font, UIStyle::PauseMenu::Item::Size),
            color);
        item.rect.x = this->_rect.x + (this->_rect.w - item.rect.w) / 2;
        item.rect.y = cursorY;
        item.draw(renderer);
        cursorY += item.rect.h + spacing;
    }

    // Indicateur bas
    if (endIdx < (int)items.size())
    {
        UIText down;
        down.setText("v", renderer,
            this->_rm.getFont(UIStyle::PauseMenu::Item::Font, UIStyle::PauseMenu::Item::Size),
            UIStyle::PauseMenu::ItemColor);
        down.rect.x = this->_rect.x + (this->_rect.w - down.rect.w) / 2;
        down.rect.y = this->_rect.y + this->_rect.h - down.rect.h - spacing;
        down.draw(renderer);
    }

    SDL_RenderSetClipRect(r, nullptr);
}

void    PauseMenuUI::render(RendererSDL &renderer)
{
    if (this->_panel == Panel::MAIN)
    {
        this->renderPanel(renderer, "PAUSE", this->_mainItems);
    }
    else if (this->_panel == Panel::GRAPHICS)
    {
        std::vector<std::string> labels;
        labels.push_back("Plein ecran / Fenetree");
        for (auto &[w, h] : this->_resolutions)
            labels.push_back(std::to_string(w) + " x " + std::to_string(h));
        this->renderPanel(renderer, "RESOLUTION", labels);
    }
    else // CONTROLS
    {
        std::vector<std::string> labels;
        for (int i = 0; i < (int)Action::COUNT; ++i)
        {
            auto &entry = this->_cfg.bindings[i];
            std::string keyName;
            if (this->_rebindingAction == i)
                keyName = this->_waitNextFrame
                    ? "..."                             // frame de transition
                    : "[ appuyez sur une touche ]";     // vraiment en attente
            else
                keyName = SDL_GetScancodeName(entry.scancode);
            labels.push_back(entry.label + "   " + keyName);
        }
        this->renderPanel(renderer, "CONTROLS", labels);
    }
}