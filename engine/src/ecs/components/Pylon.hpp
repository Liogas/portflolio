#ifndef PYLON_HPP
# define PYLON_HPP

# include <iostream>

struct Pylon
{
	std::string	listenEvent;
	bool		active;
	int			order;
	float		elapsed;
	float		goal;
};

#endif