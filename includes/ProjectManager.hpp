#ifndef PROJECTMANAGER_HPP
# define PROJECTMANAGER_HPP

# include <unordered_map>
# include <iostream>
# include <filesystem>


# include "Project.hpp"

class	ProjectManager
{
	public:
		ProjectManager();
		~ProjectManager();
		const Project	&get(const std::string &id) const;
		Project			loadProject(const std::string &id);
		std::string		getProjectPath();
	private:
		std::unordered_map<std::string, Project>	_projects;
};

#endif