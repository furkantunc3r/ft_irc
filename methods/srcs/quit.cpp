#include "../includes/quit.hpp"

Quit::Quit(std::map<int, User> &users, std::vector<pollfd> &fds) : _users(users), _fds(fds) {}

Quit::~Quit() {}

void Quit::execute(std::vector<std::string> &arg, int fd)
{
    std::vector<pollfd>::iterator it = this->_fds.begin();

    for(; it->fd != fd; it++) {}

    this->_fds.erase(it);
    this->_users.erase(fd);
    close(fd);
}