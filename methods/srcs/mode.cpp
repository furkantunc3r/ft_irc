#include "../includes/mode.hpp"

Mode::Mode(Server &server) : _server(server) {}

Mode::~Mode() {}

void Mode::execute(std::vector<std::string> &args, int fd)
{
    std::cout << ">MODE TEST<\n";
    for (size_t i = 0; i < args.size(); i++)
        std::cout << "---->ARG " << i << " " << args[i] << "<----\n";

    if (args.size() == 2)
        return;

    std::string msg;

    if (this->_server.get_channel(args[1]).get_admin_fd() != fd)
    {
        msg.append(this->_server.get_user(fd)._prefix + "NOTICE 482 :You are not operator" + "\r\n");
        send(fd, msg.c_str(), msg.size(), 0);
        return;
    }

    if (!args[3].empty())
    {
        if (args[2][0] == 'O')
        {
            if (!(this->_server.get_channel(args[1]).is_on_channel(this->_server.get_user_fd_if_on_server(args[3]))))
            {
                msg.append(this->_server.get_user(fd)._prefix + "NOTICE 441 " + args[3] + " :is not in channel" + "\r\n");
                send(fd, msg.c_str(), msg.size(), 0);
                return;
            }
            this->_server.get_channel(args[1]).make_admin(this->_server.get_user_fd_if_on_server(args[3]));
            msg.append(this->_server.get_user(fd)._prefix + "NOTICE 457 " + args[3] + " :is now the channel admin" + "\r\n");
            send(fd, msg.c_str(), msg.size(), 0);
            return;
        }

        if (args[2][0] == '+' && args[2][1] == 'k')
        {
            this->_server.get_channel(args[1]).set_pass(args[3]);
            return ;
        }
        else if (args[2][0] == '-' && args[2][1] == 'k' && this->_server.get_channel(args[1]).get_pass() == args[3])
        {
            this->_server.get_channel(args[1]).set_pass("");
            msg.append(this->_server.get_user(fd)._prefix + "475 " + this->_server.get_user(fd)._nickname + " :Incorrect channel password\r\n");
            send(fd, msg.c_str(), msg.size(), 0);
            return ;
        }

        if (args[2][0] == '+' && args[2][1] == 'l')
        {
            int limit = atoi(args[3].c_str());
            if (limit == 0)
            {
                msg.append(this->_server.get_user(fd)._prefix + "NOTICE " + this->_server.get_user(fd)._nickname + " :Wrong limit amount\r\n");
                send(fd, msg.c_str(), msg.size(), 0);
                return;
            }
            this->_server.get_channel(args[1]).set_limit(limit);
        }
    }

    if (args[2][0] == '-' && args[2][1] == 'l')
    {
        this->_server.get_channel(args[1]).set_limit(10);
        return ;
    }

    if (args[2][0] == '+' && args[2][1] == 'n')
        this->_server.get_channel(args[1]).set_narrowcast(1);
    else if (args[2][0] == '-' && args[2][1] == 'n')
        this->_server.get_channel(args[1]).set_narrowcast(0);
        
    return;
}