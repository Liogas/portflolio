#include "App.hpp"

#include <stdexcept>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	try
	{
		App app;
		app.run();
	} catch (const std::exception& e)
	{
		std::cerr << "ERROR : " << e.what() << std::endl;
	}
	return (0);
}
