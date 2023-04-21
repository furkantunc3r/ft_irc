#ifndef UTILS_HPP
#define UTILS_HPP

#include <sys/socket.h>
#include "../channel/includes/channel.hpp"
#include "unistd.h"
#include <sys/poll.h>
#include <map>

std::vector<std::string> parse(std::string str, std::string delimeter);

bool channel_validate(std::map<std::string, Channel> channels, std::string channel_name, int fd);

std::string trim(std::string& str, char delimeter);

void error(std::string msg, int fd);

#endif
