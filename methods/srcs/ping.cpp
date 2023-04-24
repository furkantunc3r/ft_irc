#include "../includes/ping.hpp"

Ping::Ping(Server& server) : _server(server) {}

Ping::~Ping() {}

void Ping::execute(std::vector<std::string>& args, int fd)
{
    std::string msg;
    
    msg.append(":localhost PONG localhost "+ this->_server.get_user(fd)._nickname + "\r\n");
    std::cout << msg << std::endl;

    send(fd, msg.c_str(), msg.size(), 0);
}