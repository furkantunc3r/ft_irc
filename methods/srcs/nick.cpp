#include "../includes/nick.hpp"

Nick::Nick(std::map<int, User> &users) : _users(users) {}

Nick::~Nick() {}

void Nick::execute(std::vector<std::string> &args, int fd)
{
    std::cout << ">NICK TEST<\n";
    for (size_t i = 0; i < args.size(); i++)
        std::cout << "---->ARG " << i << " " << args[i] << "<----\n";

    std::map<int, User>::iterator it;
    std::string msg;
	std::cout << this->_users.find(fd)->second._joinable << std::endl;
    if (this->_users.find(fd)->second._joinable != -1)
    {
        if (args.empty() || args[1].empty())
        {
            it = this->_users.find(fd);
            msg.append(it->second._prefix + " 431 " + it->second._nickname + " :Please provide a Nickname\r\n");
            send(fd, msg.c_str(), msg.size(), 0);
            return;
        }

        
        it = this->_users.begin();
        for (; it != this->_users.end(); it++)
        {
            if (it->second._nickname == args[1])
            {
                msg.append(it->second._prefix + " 433 " + it->second._nickname + " :Nickname already in use\r\n");
                send(fd, msg.c_str(), msg.size(), 0);
                if (this->_users.find(fd)->second._nickname.empty())
                    this->_users.find(fd)->second._nickname = args[1];
                return;
            }
        }

        it = this->_users.find(fd);
        msg.append(it->second._prefix + " NICK " + args[1] + "\r\n");
        send(fd, msg.c_str(), msg.size(), 0);
        it->second._nickname = args[1];
		it->second._prefix = ":" + it->second._nickname + "!" + it->second._username + "@localhost ";
    }
}