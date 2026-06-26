# include "ProjectManager.hpp"

ProjectManager::ProjectManager()
{
	std::cout << "ProjectManager created" << std::endl;
}

ProjectManager::~ProjectManager()
{
	std::cout << "ProjectManager destroyed" << std::endl;
}

const Project	&ProjectManager::get(const std::string &id) const
{
	try
	{
		auto it = this->_projects.find(id);
		if (it == this->_projects.end())
        	throw std::runtime_error("Unknown project id: " + id);
		return it->second;
	} catch (const std::exception &e)
	{
		std::cerr << "PROJETMANAGER::GET" << std::endl;
		throw (std::runtime_error(e.what()));
	}
}

std::string	ProjectManager::getProjectsPath()
{
	static std::string	path;

	if (path.empty())
	{
		auto exePath = std::filesystem::current_path();
		while (!std::filesystem::exists(exePath / "data"))
		{
			exePath = exePath.parent_path();
			if (exePath == exePath.root_path())
				throw std::runtime_error("ERROR ProjectManager::getProjectsPath : data folder not found");
		}
		path = (exePath / "data/projects").string() + "/";
	}
	return (path);
}

void	ProjectManager::loadAll()
{
	try
	{
		std::filesystem::path folder = getProjectsPath();
		for (const auto &entry : std::filesystem::directory_iterator(folder))
		{
			if (!entry.is_regular_file())
				continue ;
			if (entry.path().extension() != ".json")
				continue ;
			std::ifstream file (entry.path());
			if (!file.is_open())
				throw (std::runtime_error(
					"ERROR ProjectManager::loadAll : Cannot open computer file -> " +  entry.path().string()
				));
			nlohmann::json data;
			file >> data;
			Project	project = data.get<Project>();
			this->_projects.emplace(project.id, project);
		}
	} catch (const std::exception &e)
	{
		throw (std::runtime_error(e.what()));
	}	
}