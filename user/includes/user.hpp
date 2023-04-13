#ifndef USER_HPP
#define USER_HPP

#include <iostream>

class User
{
    private:
        int         _port;
        int         _role;
        std::string _username;
        std::string _realname;
        std::string _hostname;
        std::string _password;
    
    public:
        int         _fd;
        std::string _nickname;
        User(int fd, int port);
        User(std::string nickname, std::string username, int fd);
        ~User();
};


#endif