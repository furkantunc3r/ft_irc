#include "../includes/quit.hpp"

Quit::Quit(std::map<int, User> &users, std::vector<pollfd> &fds, std::map<std::string, Channel> &channels) : _users(users), _fds(fds), _channels(channels), LeavingBot(users, channels) {
	_message = new Message(_users, _channels);
}

Quit::~Quit() {
	delete this->_message;
}

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
    // buffer.append(":" + this->_users.find(fd)->second._nickname + "!" + this->_users.find(fd)->second._username + "@" + "localhost" + " QUIT " + arg[2]);
    send(fd, buffer.c_str(), buffer.size(), 0);
	std::string reason;
	trim(arg[2], ':');
	for (size_t i = 2; i < arg.size(); i++)
		reason.append(arg[i]);
	reason.append("\r\n");
	this->send_message(fd, reason);
    this->_fds.erase(it);
    this->_users.erase(fd);
    close(fd);
}