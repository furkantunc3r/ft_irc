#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include "../../user/includes/user.hpp"
#include <vector>
#include <cstring>
class Channel
{
    private:
        std::string				_name;
        std::vector<User>		_users;
        std::string				_password;
    
    public:
        Channel(int fd, std::string name);
        Channel(int fd, std::string name, std::string password);
		void add_user(User user);
		void kick_user(User user);
        ~Channel();
};

#endif