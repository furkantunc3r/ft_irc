#ifndef USER_HPP
#define USER_HPP

#include <iostream>

class User
{
    private:
        int         _fd;
        int         _port;
        int         _role;
        std::string _username;
        std::string _nickname;
        std::string _realname;
        std::string _hostname;
        std::string _password;
    
    public:
        User(int fd, int port);
        ~User();
};


#endif