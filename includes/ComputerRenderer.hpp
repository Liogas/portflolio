#ifndef COMPUTERRENDERER_HPP
# define COMPUTERRENDERER_HPP

# include "RendererSDL.hpp"
# include "Computer.hpp"

class ComputerRenderer
{
	public:
		ComputerRenderer();
		~ComputerRenderer();
		void	draw(RendererSDL &renderer, const Computer &computer);
};

#endif