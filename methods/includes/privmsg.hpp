#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "imethod.hpp"
#include "../../irc_bots/includes/file.hpp"
#include "../../irc_bots/includes/filter_bot.hpp"

class Privmsg : public IMethod, FilterBot
{
    private:
        std::map<int, User>&                _users;
        std::map<std::string, Channel>&     _channels;
		File								_file;
        // FilterBot                           *_bot;
    public:
        Privmsg(std::map<int, User>& users, std::map<std::string, Channel>& channels);
        ~Privmsg();
        void execute(std::vector<std::string> &args, int fd);
};

#endif