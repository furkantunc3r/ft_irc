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
        msg.append(this->_server.get_user(fd)._prefix + " 461 NOTICE" + args[1] + " :Insufficent parameters\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
    }

    Channel& chan = this->_server.get_channel(args[1]);

    if (this->_server.get_channel(args[1]).get_admin_fd() != fd)
    {
        msg.append(this->_server.get_user(fd)._prefix + "NOTICE 482 " + chan.get_name() + " :You are not operator\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
    }

    if (!chan.is_on_channel(this->_server.get_user_fd_if_on_server(args[2])))
    {
        msg.append(this->_server.get_user(fd)._prefix + " NOTICE 441 " + chan.get_name() + " :User not in channel\r\n");
		std::cout << msg << std::endl;
		send(fd, msg.c_str(), msg.size(), 0);
		return ;
    }


    msg.append(this->_server.get_user(fd)._prefix + "KICK " + chan.get_name() + " " + args[2] + "\r\n");
    // std::cout << this->_server.get_user_fd_if_on_server(args[2]) << std::endl;
	// std::cout << msg << std::endl;
    send(this->_server.get_user_fd_if_on_server(args[2]), msg.c_str(), msg.size(), 0);
    return ;


    // :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
    // :ftuncer!ftuncer1@localhost KICK #genel ftuncer_
}