#ifndef COMPUTER_HPP
# define COMPUTER_HPP

# include <iostream>
# include <vector>

# include "json.hpp"

typedef struct s_computerData
{
	std::vector<std::string>	projectIds;
}	ComputerData;

inline void from_json(
    const nlohmann::json& j,
    ComputerData& c)
{
    j.at("projectIds").get_to(c.projectIds);
}

typedef struct s_computer
{
    std::string                 title;
	std::string					id;
	bool						poweredOn;
}	Computer;

# endif