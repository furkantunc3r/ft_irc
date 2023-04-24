#ifndef QUIT_HPP
#define QUIT_HPP

#include "imethod.hpp"
// #include "message.hpp"
#include "privmsg.hpp"
#include <vector>
#include <stdlib.h>
#include "../../irc_bots/includes/leaving_bot.hpp"
class Quit : public IMethod, LeavingBot
{
    std::vector<pollfd>             	&_fds;
    std::map<int, User>			    	&_users;
	std::map<std::string, Channel>		&_channels;
    public:
		Privmsg* _message;
        Quit(std::map<int, User> &users, std::vector<pollfd> &fds, std::map<std::string, Channel> &channels);
        ~Quit();

        void execute(std::vector<std::string> &arg, int fd);
};

#endif