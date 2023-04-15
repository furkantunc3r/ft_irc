#include "../includes/quit.hpp"

Quit::Quit(std::map<int, User> &users, std::vector<pollfd> &fds) : _users(users), _fds(fds) {}

Quit::~Quit() {}

void Quit::execute(std::vector<std::string> &arg, int fd)
{
    if (arg[2].size() > 160)
    {
        send(fd, "Quit message cannot exceed 160 characters\r\n", 43, 0);
        return ;
    }
    std::string buffer;
    std::vector<pollfd>::iterator it = this->_fds.begin();

    for(; it->fd != fd; it++) {}
    buffer.append(":" + this->_users.find(fd)->second._nickname + "!" + this->_users.find(fd)->second._username + "@" + "localhost" + " QUIT " + arg[2]);
    send(fd, buffer.c_str(), buffer.size(), 0);
    this->_fds.erase(it);
    this->_users.erase(fd);
    close(fd);
}