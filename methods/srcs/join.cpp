#include "../includes/join.hpp"

Join::Join(){}

Join::~Join(){}

void Join::do_method(std::vector<std::string> arg, int fd){
	std::cout << "Join " << fd << std::endl;
}