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

    tts.append(trim(args[2], ':'));

    if (args[1][0] == '#')
    {
        std::map<std::string, Channel>::iterator ite = this->_channels.find(args[1]);
        it = this->_users.find(fd);
        if (ite == this->_channels.end())
        {
            msg.clear();
            msg.append(it->second._prefix + " 401 " + it->second._nickname + " :" + args[2] + " :No such nick or channel\r\n");
            send(it->second._fd, msg.c_str(), msg.size(), 0);
            return;   
        }
        std::vector<int> fds(ite->second.get_fds());
        for (size_t i = 0; i < fds.size(); i++)
        {
            if (fds[i] != fd)
            {
                msg.append(it->second._prefix + "PRIVMSG " + args[1] + " " + tts + "\r\n");
				
                send(this->_users.find(fds[i])->second._fd, msg.c_str(), msg.size(), 0);
            }
			std::cout << it->second._prefix << std::endl;
        }
        msg.clear();
        return ;
    }
    else 
    {
        for (it = this->_users.begin(); it != this->_users.end(); it++)
        {
            if (!strncmp(it->second._nickname.c_str(), args[1].c_str(), it->second._nickname.size()))
            {
				msg.append(this->_users.find(fd)->second._prefix + "PRIVMSG " + args[1] + " " + tts + "\r\n");
				std::cout << msg << std::endl;
                send(it->second._fd, msg.c_str(), msg.size(), 0);
                return;
            }
        }

        if (it == this->_users.end())
        {
            it = this->_users.find(fd);
            msg.clear();
            msg.append(it->second._prefix + " 401 " + it->second._nickname + " :" + args[1] + " :No such nick or channel\r\n");
            send(it->second._fd, msg.c_str(), msg.size(), 0);
            return;
        }
    }
}