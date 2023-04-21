#include "../includes/pass.hpp"

Pass::Pass(std::map<int, User>& users) : _users(users) {}

Pass::~Pass() {}

void Pass::execute(std::vector<std::string> &args, int fd)
{
	std::map<int, User>::iterator it = this->_users.find(fd);
	if (args[1].empty())
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