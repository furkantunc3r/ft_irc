#ifndef KICK_HPP
#define KICK_HPP

#include "../includes/imethod.hpp"
#include "../../server/includes/server.hpp"

class Server;

class Kick : public IMethod
{
    private:
        Server& _server;
    public:
        Kick(Server& server);
        ~Kick();
        void execute(std::vector<std::string> &args, int fd);
};

#endif