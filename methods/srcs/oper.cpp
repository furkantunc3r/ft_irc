#include "../includes/oper.hpp"

Oper::Oper(std::map<int, User>& users, std::map<int, User>& opers, std::string pass) : _users(users), _opers(opers), _pass(pass) {}

Oper::~Oper() {}

void Oper::execute(std::vector<std::string> &args, int fd)
{
    std::map<int, User>::iterator it = this->_users.find(fd);
    std::string msg;

    if (args.size() != 5 || args[2].empty() || args[4].empty())
    {
        msg.append(it->second._prefix + " 461 " + it->second._nickname + " :Insufficent parameters\r\n");
        send(fd, msg.c_str(), msg.size(), 0);
        return;
    }

    if (args[4] != this->_pass)
	{
		msg.append(it->second._prefix + " 464 " + it->second._nickname + " :Wrong Oper Pass\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
	}

    this->_opers.insert(std::make_pair(it->first, it->second));
    msg.append(it->second._prefix + " 381 " + it->second._nickname + " :You are now an IRC operator\r\n");
    send(fd, msg.c_str(), msg.size(), 0);
    return ;
}