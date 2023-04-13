#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>

class Channel
{
    private:
        std::string _name;
        std::string _users;
        std::string _password;
    
    public:
        Channel(std::string name);
        Channel(std::string name, std::string password);
        ~Channel();
};

#endif