#include "../includes/dcc.hpp"

Dcc::Dcc()
{
	memset(&this->addr, 0, sizeof(this->addr));
}

Dcc::~Dcc(){}

void	Dcc::execute(const std::vector<std::string> &args)
{
	// set_addr(args[3], args[4]);
	memset(&this->addr, 0, sizeof(this->addr));
	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = inet_addr(args[3].c_str());
	this->addr.sin_port = htons(std::atoi(args[4].c_str()));
	this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listen_fd < 0)
		error("socket () failed ", this->listen_fd);
	close(listen_fd);
}