#ifndef PASS_HPP
#define PASS_HPP

#include "../../server/includes/server.hpp"

class Pass : public IMethod
{
    private:
        std::map<int, User>&    _users;
        std::string             _pass;
    public:
        Pass(std::map<int, User>& users, std::string pass);
        ~Pass();
        void execute(std::vector<std::string> &args, int fd);

};

#endif