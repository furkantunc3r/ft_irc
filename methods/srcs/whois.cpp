#include "../includes/wohis.hpp"

Whois::Whois(){}

Whois::~Whois(){}

void Whois::do_method(std::vector<std::string> arg, int fd)
{
	std::cout << "Whois " << fd << std::endl;
}