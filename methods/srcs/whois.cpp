#include "../includes/wohis.hpp"

Whois::Whois(){}

Whois::~Whois(){}

void Whois::execute(std::vector<std::string>& arg, int fd)
{
	std::cout << "Whois " << fd << std::endl;
}