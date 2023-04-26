#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>

class User
{
    public:
        std::string					_password;
        int                         _fd;
        std::string                 _nickname;
        std::string                 _username;
        std::string 				_realname;
        std::vector<std::string>	_channels;
        int                         _joinable;
        int                         _is_regis;
		std::string					_prefix;
		
        User(int fd, std::string ip);
        User(std::string nickname, std::string username, int fd);
        ~User();
};


#endif