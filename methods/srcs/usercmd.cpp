#include "../includes/usercmd.hpp"

Usercmd::Usercmd(std::map<int, User>& users) : _users(users) {}

Usercmd::~Usercmd() {}

void Usercmd::execute(std::vector<std::string> &args, int fd)
{
    std::map<int, User>::iterator it = this->_users.find(fd);
    std::string msg;
    
    if (args.size() < 4)
    {
        it = this->_users.find(fd);
        msg.append(":" + it->second._nickname + "!" + it->second._username + "localhost" + " 461 " + it->second._nickname + " :Insufficent parameters\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
    }
    
    if (it != this->_users.end())
	{
		msg.append(":" + it->second._nickname + "!" + it->second._username + "localhost" + " 462 " + it->second._nickname + " :You are already registered\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
	}

    it->second._username = args[2];
    it->second._realname = args[8];
}