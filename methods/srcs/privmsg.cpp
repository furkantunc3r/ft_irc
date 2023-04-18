#include "../includes/privmsg.hpp"

Privmsg::Privmsg(std::map<int, User> &users, std::map<std::string, Channel> &channels) : _users(users), _channels(channels) {}

Privmsg::~Privmsg() {}

void Privmsg::execute(std::vector<std::string> &args, int fd)
{
    std::cout << ">Privmsg TEST<\n";
	for (size_t i = 0; i < args.size(); i++)
		std::cout << "---->ARG " << i << " " << args[i] << "<----\n";

    std::map<int, User>::iterator it;
    std::string msg;
    std::string tts;

    if (args.size() < 2 || args[0].empty() || args[1].empty())
    {
        msg.append(":" + it->second._nickname + "!" + it->second._username + "localhost" + " 461 " + it->second._nickname + " :Insufficent parameters\r\n");
        send(fd, msg.c_str(), msg.size(), 0);
        return;
    }

    for (size_t i = 4; i < args.size(); i++)
            tts.append(args[i]);

    if (args[2].at(0) == '#')
    {
        std::map<std::string, Channel>::iterator ite = this->_channels.find(args[2]);
        if (ite == this->_channels.end())
        {
            it = this->_users.find(fd);
            msg.clear();
            msg.append(":" + it->second._nickname + "!" + it->second._username + "localhost" + " 401 " + it->second._nickname + " :" + args[2] + " :No such nick or channel\r\n");
            send(it->second._fd, msg.c_str(), msg.size(), 0);
            return;   
        }
        std::vector<int> fds(ite->second.get_fds());
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i] != fd)
            {
                msg.append(":" + this->_users.find(fd)->second._nickname + "!" + this->_users.find(fd)->second._username + "@localhost " + "PRIVMSG " + args[2] + " " + tts + "\r\n");
                send(this->_users.find(fds[i])->second._fd, msg.c_str(), msg.size(), 0);
            }
        }
        msg.clear();
        return ;
    }
    else 
    {
        msg.append(":" + this->_users.find(fd)->second._nickname + "!" + this->_users.find(fd)->second._username + "@localhost " + "PRIVMSG " + args[2] + " " + tts + "\r\n");
        for (it = this->_users.begin(); it != this->_users.end(); it++)
        {
            if (it->second._nickname == args[2])
            {
                send(it->second._fd, msg.c_str(), msg.size(), 0);
                return;
            }
        }

        if (it == this->_users.end())
        {
            it = this->_users.find(fd);
            msg.clear();
            msg.append(":" + it->second._nickname + "!" + it->second._username + "localhost" + " 401 " + it->second._nickname + " :" + args[2] + " :No such nick or channel\r\n");
            send(it->second._fd, msg.c_str(), msg.size(), 0);
            return;
        }
    }
}