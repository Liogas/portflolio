#ifndef COMPUTERUIFACTORY_HPP
# define COMPUTERUIFACTORY_HPP

# include "ComputerUI.hpp"
# include "Computer.hpp"
# include "ProjectManager.hpp"
# include "CarousselFactory.hpp"
# include "TitleBarFactory.hpp"

class	ComputerUIFactory
{
    public:
        ComputerUIFactory() = delete;
        static ComputerUI	create(
            const ComputerData		&data,
			const ProjectManager	&pm,
			RessourceManager		&rm,
			RendererSDL		&renderer
		);
};

#endif