#include "ComputerManager.hpp"

const ComputerData	&ComputerManager::get(const std::string &id)
{
	return (this->_computers.at(id));
}