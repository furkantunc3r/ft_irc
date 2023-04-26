#include "../includes/channel.hpp"
#include <sys/socket.h>
#include <map>

// Channel::Channel(int fd, std::string name, std::string password, std::map<int, User>& users) : _name(name) , _password(password), _users(users)
// {
// 	if (std::find(_fds.begin(), _fds.end(), fd) == _fds.end())
// 		this->_fds.push_back(fd);
// }

Channel::Channel(int fd, std::string name, std::map<int, User>& users) : _name(name), _users(users), _password("")
{
	if (std::find(_fds.begin(), _fds.end(), fd) == _fds.end())
		this->_fds.push_back(fd);
}

void Channel::add_user(int fd)
{
	if (std::find(_fds.begin(), _fds.end(), fd) == _fds.end())
		this->_fds.push_back(fd);
}

void Channel::make_admin(int fd)
{
	std::map<int, User>::iterator it = this->_users.find(fd);

	if (it != this->_users.end())
	{
		std::string msg;
		msg.append(it->second._prefix + " NOTICE " + this->_name + " :You are now the channel operator\r\n");
		this->_admin_fd = it->second._fd;
		send(it->second._fd, msg.c_str(), msg.size(), 0);
	}
}

void Channel::set_admin_fd(int fd){
	this->_admin_fd = fd;
}

void Channel::erase_user(int fd)
{
	std::vector<int>::iterator fd_it = std::find(_fds.begin(), _fds.end(), fd);
	if (fd_it != _fds.end())
		_fds.erase(fd_it);
}

int Channel::get_admin_fd()
{
	return this->_admin_fd;
}

const std::string Channel::get_name() const
{
	return this->_name;
}

std::vector<int>& Channel::get_fds()
{
	return this->_fds;
}



bool Channel::is_on_channel(int fd)
{
	if (fd == 0)
		return 0;
		
	std::vector<int>::iterator it = this->_fds.begin();

	for (; it != this->_fds.end(); it++)
		if (*it == fd)
			return 1;
	return 0;
}

std::string Channel::get_pass()
{
	return this->_password;
}

void Channel::set_pass(std::string pass)
{
	this->_password = pass;
}

Channel::~Channel() {}