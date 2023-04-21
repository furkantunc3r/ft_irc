#ifndef NICK_HPP
#define NICK_HPP

#include "imethod.hpp"

class Nick : public IMethod
{
    private:
        std::map<int, User>&    _users;
    public:
        Nick(std::map<int, User>& users);
        ~Nick();
        void execute(std::vector<std::string> &args, int fd);
};

#endif