#ifndef PROJECTMANAGER_HPP
# define PROJECTMANAGER_HPP

# include <unordered_map>
# include <iostream>
# include <filesystem>
# include <fstream>

# include "Computer.hpp"

class	ProjectManager
{
	public:
		ProjectManager();
		~ProjectManager();
		const Project	&get(const std::string &id) const;
		void			loadAll();
		std::string		getProjectsPath();
	private:
		std::unordered_map<std::string, Project>	_projects;
};

#endif