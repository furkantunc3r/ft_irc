#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "../../user/includes/user.hpp"


//send semantiği private mesaj için "PRIVMSG " + target_user + " :" + message;

class Channel
{
    private:
        std::string				_name;
        std::vector<int>		_fds;
        std::string				_password;
    
    public:
        Channel(int fd, std::string name);
        Channel(int fd, std::string name, std::string password);
		const std::string	get_name() const;
		void 				add_user(int fd);
		void 				kick_user(User user);
		std::vector<int>& 	get_fds();
        ~Channel();
};

#endif