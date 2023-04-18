#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>

class User
{
    private:
        int         				_port;
        int         				_role;
        std::string					_password;
    
    public:
        int                         _fd;
        std::string                 _nickname;
        std::string                 _username;
        std::string 				_realname;
        std::vector<std::string>	_channels;
        int                         _joinable;
        int                         _is_regis;
		
        User(int fd, int port);
        User(std::string nickname, std::string username, int fd);
        ~User();
};


#endif