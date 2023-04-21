#include "../includes/quit.hpp"

Quit::Quit(std::map<int, User> &users, std::vector<pollfd> &fds, std::map<std::string, Channel> &channels) : _users(users), _fds(fds), _channels(channels), LeavingBot(users, channels) {
	_message = new Privmsg(_users, _channels);
}

Quit::~Quit() {
	delete this->_message;
}

void Quit::execute(std::vector<std::string> &arg, int fd)
{
    if (arg[1].size() > 160)
    {
        send(fd, "Quit message cannot exceed 160 characters\r\n", 43, 0);
        return ;
    }
    std::string buffer;
    std::vector<pollfd>::iterator it = this->_fds.begin();
    for(; it->fd != fd; it++) {}
	std::string reason;
	reason.append(trim(arg.back(), ':'));
	reason.append("\r\n");
	this->send_message(fd, reason);
    this->_fds.erase(it);
	std::map<int, User>::iterator _user_it = this->_users.find(fd);
    if (_user_it != this->_users.end())
		this->_users.erase(_user_it);
    shutdown(fd, 2);
}