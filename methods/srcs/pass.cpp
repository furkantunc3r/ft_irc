#include "../includes/pass.hpp"

Pass::Pass(std::map<int, User>& users, std::string pass) : _users(users), _pass(pass) {}

Pass::~Pass() {}

void Pass::execute(std::vector<std::string> &args, int fd)
{
	std::cout << "---->PASS TEST<----\n";
	for (size_t i = 0; i < args.size(); i++)
		std::cout << "---->ARG " << i << " " << args[i] << "<----\n";
	

	if (args[2] != this->_pass)
	{
		std::string msg;
		msg.append("Password wrong or Nickname already in use\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		close(fd);
		this->_users.erase(this->_users.find(fd));
		return ;
	}
	
	std::map<int, User>::iterator it = this->_users.find(fd);
	if (args[2].empty())
	{
		std::string msg;
		msg.append(":" + it->second._nickname + "!" + it->second._username + "localhost" + " 461 " + it->second._nickname + " :Insufficent parameters\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
	}
    if (it != this->_users.end())
	{
		std::string msg;
		msg.append(":" + it->second._nickname + "!" + it->second._username + "localhost" + " 462 " + it->second._nickname + " :You are already registered\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
	}
}