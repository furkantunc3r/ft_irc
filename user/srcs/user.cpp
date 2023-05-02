#include "../includes/user.hpp"

User::User(std::string nickname, std::string username, int fd) :  _fd(fd), _nickname(nickname), _username(username), _joinable(-1), _is_regis(0) {
	this->_prefix = ":" + this->_nickname + "!" + this->_username + "@localhost ";
}

User::~User() {}