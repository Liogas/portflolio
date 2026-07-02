#ifndef COMPUTERMANAGER_HPP
# define COMPUTERMANAGER_HPP

# include <unordered_map>
# include "ecs/components/Computer.hpp"
# include <filesystem>
# include <fstream>

class ComputerManager
{
	public:
		const ComputerData	&get(const std::string &id) const;
		void				loadAll();
		std::string			getComputersPath();
	private:
		std::unordered_map<std::string, ComputerData>	_computers;
};

#endif