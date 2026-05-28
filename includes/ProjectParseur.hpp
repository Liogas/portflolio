#ifndef PROJECTPARSEUR_HPP
# define PROJECTPARSEUR_HPP

# include <iostream>
# include <filesystem>
# include <fstream>

# include "Computer.hpp"

# include "tinyxml2.h"
# include "json.hpp"

# include "ComputerFactories.hpp"

class ProjectParseur
{
	public:
		ProjectParseur() = delete;
		static Project &start(
			const std::string &path,
			World	&world
		);
};

#endif