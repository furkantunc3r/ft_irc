#ifndef QUIT_HPP
#define QUIT_HPP

#include "imethod.hpp"

class Quit : public IMethod
{
    std::vector<pollfd>             &_fds;
    std::map<int, User>			    &_users;
    public:
        Quit(std::map<int, User> &users, std::vector<pollfd> &fds);
        ~Quit();

        void execute(std::vector<std::string> &arg, int fd);
};

#endif