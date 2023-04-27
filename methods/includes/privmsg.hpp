#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "imethod.hpp"

class Privmsg : public IMethod
{
    private:
        std::map<int, User>&                _users;
        std::map<std::string, Channel>&     _channels;
    public:
        Privmsg(std::map<int, User>& users, std::map<std::string, Channel>& channels);
        ~Privmsg();
        void execute(std::vector<std::string> &args, int fd);
};


#endif