#ifndef COMPUTER_HPP
# define COMPUTER_HPP

# include <iostream>
# include <vector>

# include "json.hpp"

typedef struct	s_project
{
	std::string					id;
	std::string					title;
	std::string					description;
	std::vector<std::string>	tags;
	std::string					imgPath;
	std::string					githubUrl;
}	Project;

inline void from_json(
    const nlohmann::json& j,
    Project& p)
{
    j.at("id").get_to(p.id);
    j.at("title").get_to(p.title);
    j.at("description").get_to(p.description);
    j.at("tags").get_to(p.tags);
    j.at("imagePath").get_to(p.imgPath);
    j.at("githubUrl").get_to(p.githubUrl);
}

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
	std::string					id;
	bool						poweredOn;
}	Computer;

# endif