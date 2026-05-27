#ifndef COMPUTER_HPP
# define COMPUTER_HPP

# include <iostream>
# include <vector>

typedef struct	s_project
{
	std::string					title;
	std::string					description;
	std::vector<std::string>	tags;
	std::string					imgPath;
	std::string					githubUrl;
}	Project;

typedef struct s_computer
{
	std::vector<std::string>	messages;
	bool						poweredOn;
}	Computer;

# endif