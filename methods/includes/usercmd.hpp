#ifndef USERCMD_HPP
#define USERCMD_HPP

#include "imethod.hpp"

class Usercmd : public IMethod
{
    private:
        std::map<int, User>&    _users;
    public:
        Usercmd(std::map<int, User>& users);
        ~Usercmd();
        void execute(std::vector<std::string> &args, int fd);

};

#endif