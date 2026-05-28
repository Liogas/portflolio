# include "ProjectManager.hpp"

ProjectManager::ProjectManager()
{
	std::cout << "ProjectManager created" << std::endl;
}

ProjectManager::~ProjectManager()
{
	std::cout << "ProjectManager destroyed" << std::endl;
}

const Project	&ProjectManager::get(const std::string &id)
{
	if (!this->_projects.contains(id))
		this->_projects.emplace(id, loadProject(id));
	return (this->_projects.at(id));
}

std::string	ProjectManager::getProjectPath()
{
	static std::string	path;

	if (path.empty())
	{
		auto exePath = std::filesystem::current_path();
		while (!std::filesystem::exists(exePath / "data"))
		{
			exePath = exePath.parent_path();
			if (exePath == exePath.root_path())
				throw std::runtime_error("ERROR ProjectManager::getProjectPath : data folder not found");
		}
		path = (exePath / "data/").string() + "/";
	}
	return (path);
}

Project	ProjectManager::loadProject(const std::string &id)
{
	auto path = getProjectPath() / (id + ".json");
	
}