#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "imethod.hpp"
#include "../../channel/includes/channel.hpp"

class Message : public IMethod{
	std::map<std::string, Channel>&	_channels;	
	std::map<int, User>&			_users;
	
	public:
		Message(std::map<int, User> &users, std::map<std::string, Channel> &channels);
		~Message();

		void execute(std::vector<std::string> &arg, int fd);

};

#endif