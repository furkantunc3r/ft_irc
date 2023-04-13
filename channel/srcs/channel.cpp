#include "../includes/channel.hpp"

Channel::Channel(int fd, std::string name, std::string password) : _name(name) , _password(password) {
	User admin(fd, 0);
	this->add_user(admin);
}

Channel::Channel(int fd, std::string name) : _name(name) {
	User admin(fd, 0);
	this->add_user(admin);
}

void Channel::add_user(User user)
{
	this->_users.push_back(user);
}

Channel::~Channel() {}