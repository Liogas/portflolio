#ifndef TRIGGER_HPP
# define TRIGGER_HPP

# include <iostream>

struct	Trigger
{
    std::string	emit;
	std::string	id;
	std::string	animation;
	float		duration;
	float		elapsed;
	bool		once;
	bool		fired;
	bool		active;
};

#endif