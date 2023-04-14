#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "imethod.hpp"
#include "../../channel/includes/channel.hpp"

class Message : public IMethod{
	std::map<std::string, Channel>&	_channels;	
	
	public:
		Message(std::map<std::string, Channel>& channel);
		~Message();

		void execute(std::vector<std::string> &arg, int fd);

};

#endif