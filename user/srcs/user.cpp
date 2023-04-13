#include "../includes/user.hpp"

User::User(int fd, int port) : _fd(fd), _port(port) {}

User::User(std::string nickname, std::string username, int fd) : _nickname(nickname), _username(username), _fd(fd) {}

User::~User() {}