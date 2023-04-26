#include "../includes/channel.hpp"
#include <sys/socket.h>
#include <map>

// Channel::Channel(int fd, std::string name, std::string password, std::map<int, User>& users) : _name(name) , _password(password), _users(users)
// {
// 	if (std::find(_fds.begin(), _fds.end(), fd) == _fds.end())
// 		this->_fds.push_back(fd);
// }

Channel::Channel(int fd, std::string name, std::map<int, User>& users) : _name(name), _users(users), _password(""), _limit(11)
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
	std::map<int, User>::iterator it = this->_users.begin();

	for (; it != this->_users.end(); it++)
		if (it->second._fd == fd)
			break ;
	
	std::string msg;
	msg.append(":" + it->second._nickname + "!" + it->second._username + "@localhost" + " NOTICE " + it->second._nickname + " :You are now the channel operator\r\n");
	this->_admin_fd = it->second._fd;
	send(it->second._fd, msg.c_str(), msg.size(), 0);
}

void Channel::erase_user(int fd)
{
	std::vector<int>::iterator fd_it = std::find(_fds.begin(), _fds.end(), fd);
	if (fd_it != _fds.end())
		_fds.erase(fd_it);
	// std::cout << _users.size() << std::endl;
}

int Channel::get_admin_fd()
{
	return this->_admin_fd;
}

void Channel::set_admin_fd(int fd)
{
	this->_admin_fd = fd;
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

int	Channel::get_limit()
{
	return this->_limit;
}

void Channel::set_limit(int limit)
{
	this->_limit = limit;
}

void Channel::set_narrowcast(int val)
{
	this->_narrowcast = val;
}

int Channel::get_narrowcast()
{
	return this->_narrowcast;
}

Channel::~Channel() {}