#ifndef PAUSEMENUUI_HPP
# define PAUSEMENUUI_HPP

# include "UIWindow.hpp"
# include "UIText.hpp"
# include "UIStyle.hpp"
# include "RendererSDL.hpp"
# include "resources/ResourceManager.hpp"
# include "events/Events.hpp"
# include "config/ControlsConfig.hpp"
# include <entt/entt.hpp>
# include <vector>
# include <string>

class PauseMenuUI : public UIWindow
{
    public:
        PauseMenuUI(
			RendererSDL 		&renderer,
			ResourceManager 	&rm,
			entt::dispatcher 	&dispatcher,
			ControlsConfig		&controls
		);
        void    handleInput(const InputSDL &input) override;
        void    update(float dt) override;
        void    render(RendererSDL &renderer) override;
        bool    blocksGameplay() const override;
        bool    shouldClose()    const override;
		void	updateScroll(int count);
    private:
        enum class Panel { MAIN, GRAPHICS, CONTROLS };

        void    buildItemTextures();
        void    confirm();
        void    renderPanel(RendererSDL &renderer, const std::string &title, const std::vector<std::string> &items);

        RendererSDL         											&_renderer;
        ResourceManager    											&_rm;
        entt::dispatcher    											&_dispatcher;
        Panel               											_panel;
        int                 											_selected;
        bool                											_closeRequested;
        SDL_Rect            											_rect;
        ControlsConfig      											&_cfg;
        int                 											_rebindingAction;
		bool															_waitNextFrame;
        static const std::vector<std::string>               			_mainItems;
        static const std::vector<std::pair<int,int>>        			_resolutions;
        static const std::vector<std::pair<std::string,std::string>>	_controls;
		int																_scrollOffset;
};

#endif