#ifndef OPER_HPP
#define OPER_HPP

#include "../../server/includes/server.hpp"

class Oper : public IMethod
{
    private:
        std::map<int, User>&    _users;
        std::map<int, User>&    _opers;
        std::string             _pass;
    public:
        Oper(std::map<int, User>& users, std::map<int, User>& opers, std::string pass);
        ~Oper();
        void execute(std::vector<std::string> &args, int fd);

};

#endif