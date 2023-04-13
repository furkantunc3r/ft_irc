#include "../includes/channel.hpp"

Channel::Channel(std::string name, std::string password) : _name(name) , _password(password) {}

Channel::Channel(std::string name) : _name(name) {}

Channel::~Channel() {}