#ifndef COMPUTERMANAGER_HPP
# define COMPUTERMANAGER_HPP

# include <unordered_map>
# include "Computer.hpp"

class ComputerManager
{
	public:
		const ComputerData &get(const std::string &id);
		void	loadAll();
	private:
		std::unordered_map<std::string, ComputerData>	_computers;
};

#endif