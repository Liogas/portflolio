#ifndef COMPUTER_HPP
# define COMPUTER_HPP

# include <iostream>
# include <vector>

# include <json/json.hpp>

typedef struct s_computerData
{
    std::string                 title;
	std::vector<std::string>	projectIds;
}	ComputerData;

inline void from_json(
    const nlohmann::json& j,
    ComputerData& c)
{
    j.at("projectIds").get_to(c.projectIds);
    j.at("title").get_to(c.title);
}

typedef struct s_computer
{
	std::string					id;
	bool						poweredOn;
}	Computer;

# endif