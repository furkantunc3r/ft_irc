#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "../../user/includes/user.hpp"
#include <map>

class Channel
{
    private:
        int                     _admin_fd;
        std::string				_name;

        std::vector<int>		_fds;

        std::map<int, User>&    _users;
        std::string				_password;
        int                     _limit;
        int                     _narrowcast;
    
    public:
        Channel(int fd, std::string name, std::map<int, User>& users);
        // Channel(int fd, std::string name, std::string password, std::map<int, User>& users);
        void                make_admin(int fd);
		const std::string	get_name() const;
		void 				add_user(int fd);
		void 				kick_user(User user);
		std::vector<int>& 	get_fds();
        bool                is_on_channel(int fd);
        int                 get_admin_fd();
		void				erase_user(int fd);
        std::string         get_pass();
        void                set_pass(std::string pass);
        int                 get_limit();
        void                set_limit(int limit);
        int                 get_narrowcast();
        void                set_narrowcast(int val);
        ~Channel();
};

#endif