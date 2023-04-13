#include "../includes/channel.hpp"

Channel::Channel(int fd, std::string name, std::string password) : _name(name) , _password(password) {
	if (std::find(_fds.begin(), _fds.end(), fd) == _fds.end())
		this->_fds.push_back(fd);
}

Channel::Channel(int fd, std::string name) : _name(name) {
	if (std::find(_fds.begin(), _fds.end(), fd) == _fds.end())
		this->_fds.push_back(fd);
}

void Channel::add_user(int fd)
{
	if (std::find(_fds.begin(), _fds.end(), fd) == _fds.end())
		this->_fds.push_back(fd);
	std::cout <<"channel fd size :" <<this->_fds.size() << std::endl;

}

const std::string Channel::get_name() const {
	return this->_name;
}

std::vector<int>& Channel::get_fds(){
	return this->_fds;
}

Channel::~Channel() {}