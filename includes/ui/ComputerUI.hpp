#ifndef COMPUTERUI_HPP
# define COMPUTERUI_HPP

# include "ComputerManager.hpp"

# include "UIWindow.hpp"

# include "ProjectCard.hpp"
# include "Caroussel.hpp"

# include "UIStyle.hpp"

struct	ComputerUI
{
	UIText		title;
	Caroussel	caroussel;
	SDL_Rect	rect;
};

class ComputerUI : public UIWindow
{
	public:
		ComputerUI(
			const std::string	&id,
			ComputerManager		&cm
		);
		void	init(
    		RessourceManager        &rm,
    		RendererSDL             &renderer,
    		const ProjectManager    &pm
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
		RendererSDL			&_renderer;
		RessourceManager	&_rm;
};

#endif