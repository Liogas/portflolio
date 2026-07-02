#include "ui/manager/ComputerManager.hpp"

const ComputerData	&ComputerManager::get(const std::string &id) const
{
	return (this->_computers.at(id));
}

void	ComputerManager::loadAll()
{
	try
	{
		std::filesystem::path folder = getComputersPath();
		for (const auto &entry : std::filesystem::directory_iterator(folder))
		{
			if (!entry.is_regular_file())
				continue ;
			if (entry.path().extension() != ".json")
				continue ;
			std::cout << "Computer file -> " << entry.path() << std::endl;
			std::ifstream file (entry.path());
			if (!file.is_open())
				throw (std::runtime_error(
					"ERROR ComputerManager::loadAll : Cannot open computer file -> " +  entry.path().string()
				));
			nlohmann::json data;
			file >> data;
			std::string	id = data.at("id").get<std::string>();
			ComputerData computer = data.get<ComputerData>();
			this->_computers.emplace(id, computer);
		}
	} catch (const std::exception &e)
	{
		throw (std::runtime_error(e.what()));
	}
}

std::string	ComputerManager::getComputersPath()
{
	static std::string	path;

	if (path.empty())
	{
		auto exePath = std::filesystem::current_path();
		while (!std::filesystem::exists(exePath / "data"))
		{
			exePath = exePath.parent_path();
			if (exePath == exePath.root_path())
				throw std::runtime_error("ERROR ComputerManager::getComputersPath : data folder not found");
		}
		path = (exePath / "data/computers").string() + "/";
	}
	return (path);
}
