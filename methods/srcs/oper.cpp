#include "../includes/oper.hpp"

Oper::Oper(std::map<int, User>& users, std::map<int, User>& opers, std::string pass) : _users(users), _pass(pass), _opers(opers) {}

Oper::~Oper() {}

void Oper::execute(std::vector<std::string> &args, int fd)
{
    std::map<int, User>::iterator it = this->_users.find(fd);
    std::string msg;

    if (args.size() != 5 || args[2].empty() || args[4].empty())
    {
        msg.append(":" + it->second._nickname + "!" + it->second._username + "localhost" + " 461 " + it->second._nickname + " :Insufficent parameters\r\n");
        send(fd, msg.c_str(), msg.size(), 0);
        return;
    }

    if (args[4] != this->_pass)
	{
		msg.append(":" + it->second._nickname + "!" + it->second._username + "localhost" + " 464 " + it->second._nickname + " :Wrong Oper Pass\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
	}

    it->second._role = 1;
    this->_opers.insert(std::make_pair(it->first, it->second));
    msg.append(":" + it->second._nickname + "!" + it->second._username + "localhost" + " 381 " + it->second._nickname + " :You are now an IRC operator\r\n");
    send(fd, msg.c_str(), msg.size(), 0);
    return ;
}