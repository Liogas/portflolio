#ifndef COMPUTER_HPP
# define COMPUTER_HPP

# include <iostream>
# include <vector>

typedef struct s_computer
{
	std::vector<std::string>	messages;
	bool						poweredOn;
}	Computer;

# endif