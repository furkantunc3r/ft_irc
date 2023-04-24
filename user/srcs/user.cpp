#include "../includes/user.hpp"

User::User(int fd, int port) : _fd(fd), _port(port), _joinable(1), _is_regis(0) {}

User::User(std::string nickname, std::string username, int fd) : _nickname(nickname), _username(username), _fd(fd), _joinable(1), _is_regis(0) {
	this->_prefix = ":" + this->_nickname + "!" + this->_username + "@localhost ";
}

User::~User() {}