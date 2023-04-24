#include "../includes/kick.hpp"

Kick::Kick(Server& server) : _server(server) {}

Kick::~Kick() {}

void Kick::execute(std::vector<std::string> &args, int fd)
{
    std::cout << ">KICK TEST<\n";
    for (size_t i = 0; i < args.size(); i++)
        std::cout << "---->ARG " << i << " " << args[i] << "<----\n";

    std::string msg;

    if (args.size() < 3 || args.size() > 4)
    {
        msg.append(":" + this->_server.get_user(fd)._nickname + "!" + this->_server.get_user(fd)._username + "@localhost" + " 461 " + this->_server.get_user(fd)._nickname + " :Insufficent parameters\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
    }

    Channel& chan = this->_server.get_channel(args[1]);

    if (this->_server.get_channel(args[1]).get_admin_fd() != fd)
    {
        msg.append(":" + this->_server.get_user(fd)._nickname + "!" + this->_server.get_user(fd)._username + "@localhost" + " 482 " + this->_server.get_user(fd)._nickname + " :You are not operator\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
    }

    if (!chan.is_on_channel(this->_server.get_user_fd_if_on_server(args[2])))
    {
        msg.append(":" + this->_server.get_user(fd)._nickname + "!" + this->_server.get_user(fd)._username + "@localhost" + " 441 " + this->_server.get_user(fd)._nickname + " :User not in channel\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
    }

    msg.append(":" + this->_server.get_user(fd)._nickname + "!" + this->_server.get_user(fd)._username + "@localhost" + " KICK " + args[1] + " " + args[2] + "\r\n");
    std::cout << msg << std::endl;
    std::cout << this->_server.get_user_fd_if_on_server(args[2]) << std::endl;
    send(this->_server.get_user_fd_if_on_server(args[2]), msg.c_str(), msg.size(), 0);
    return ;


    // :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
    // :ftuncer!ftuncer1@localhost KICK #genel ftuncer_
}