#ifndef PORTFOLIOUI_HPP
# define PORTFOLIOUI_HPP

# include "ComputerManager.hpp"

# include "UIWindow.hpp"

# include "ProjectCard.hpp"
# include "Caroussel.hpp"

# include "UIStyle.hpp"

class PortfolioUI : public UIWindow
{
	public:
		PortfolioUI(
			const std::string		&id,
			ComputerManager			&cm,
			ResourceManager			&rm,
    		const ProjectManager	&pm,
    		RendererSDL				&renderer
		);
		void	update(float dt) 					override;
		void	render(RendererSDL &renderer) 		override;
		bool	blocksGameplay() const 				override;
		void	handleInput(const InputSDL &input)	override;
		bool	shouldClose() const					override;
	private:
		std::string			_id;
		UIText				_title;
		Caroussel			_caroussel;
		SDL_Rect			_rect;
		bool				_closeRequested;
		const ComputerData	&_data;
		ResourceManager		&_rm;
		RendererSDL			&_renderer;
};

#endif