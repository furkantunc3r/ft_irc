#ifndef PING_HPP
#define PING_HPP

#include "imethod.hpp"
#include "../../server/includes/server.hpp"

class Ping : public IMethod
{
    private:
        Server& _server;
    public:
        Ping(Server& server);
        ~Ping();
        void execute(std::vector<std::string>& args, int fd);
};

#endif