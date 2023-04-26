#include "../includes/ping.hpp"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

Ping::Ping(Server& server) : _server(server) {}

Ping::~Ping() {}

void Ping::execute(std::vector<std::string>& args, int fd)
{
    std::string msg;

    msg.append(":localhost PONG localhost " + args[1] + "\r\n");
    send(fd, msg.c_str(), msg.size(), 0);
}