#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "imethod.hpp"
#include "../../channel/includes/channel.hpp"

class Message : public IMethod{
	std::vector<Channel>&	_channel;	
	
	public:
		Message(std::vector<Channel>& channel);
		~Message();

		void execute(std::vector<std::string> &arg, int fd);

};

#endif