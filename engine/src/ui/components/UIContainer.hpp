#ifndef UICONTAINER_HPP
# define UICONTAINER_HPP

# include "UIElement.hpp"

class UIContainer : public UIElement
{
    public:
        void    setLayout(LayoutType l);
        void    setPadding(int p);
        void    setSpacing(int s);
        void    add(UIElement *e);
        void    draw(RendererSDL &r) override;
        void    updateLayout();
    private:
        LayoutType              _layout;
        std::vector<UIElement*> _children;
        int                     _padding;
        int                     _spacing;
        void    layoutVertical();
        void    layoutHorizontal();
};

#endif