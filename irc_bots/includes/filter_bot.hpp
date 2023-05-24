#ifndef FILTER_BOT_HPP
#define FILTER_BOT_HPP

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include "../../user/includes/user.hpp"
#include "../../channel/includes/channel.hpp"
#include "../../utils/utils.hpp"

class FilterBot
{
    private:
        std::map<int, User>					&_users;
		std::map<std::string, Channel>		&_channels;
		std::vector<std::string>			_blacklist_words;
    public:
        FilterBot(std::map<int, User> &_users, std::map<std::string, Channel> &_channels);
        ~FilterBot();

        int check_message(int fd, std::string msg);
};

#endif