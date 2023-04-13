#include "../includes/join.hpp"

Join::Join(){}

Join::~Join(){}

void Join::do_method(std::vector<std::string> &arg, int fd)
{
	for (size_t i = 0; i < arg.size(); i++)
	{
		std::cout << arg[i] << std::endl;
	}
	// Channel cha(fd ,arg[1]);
	std::string a(":ali!localhost JOIN ");
	a.append(arg[1] + "\r\n");
	send(fd, a.c_str(), a.length(), 0);
}