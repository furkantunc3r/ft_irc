#include "../includes/message.hpp"

Message::Message(std::vector<Channel>& channel) : _channel(channel){}

Message::~Message(){}

void Message::execute(std::vector<std::string> &arg, int fd){
	std::string msg;
	msg.append(":acetin1!Abdullah1@localhost "); //dinamik yap
	msg.append("PRIVMSG " + arg[2] + " :");
	for (size_t i = 4; i < arg.size(); i++)
		msg.append(trim(arg[i], ':'));
	msg.append("\r\n");
	if (!does_exist_channel(this->_channel, arg[2], fd))
	{
		for (size_t i = 0; i < this->_channel.size(); i++)
		{
			std::cout << "channle size : "<<this->_channel.size() << std::endl;
			if(!strncmp(_channel[i].get_name().c_str(), arg[2].c_str(), _channel[i].get_name().size()))
			{
				std::cout << "aaaaaaaaaaaaaaaa\n";
				char buffer[4096];
				for (size_t j = 0; j < _channel[i].get_fds().size(); j++)
				{
					std::cout << "fd : "<<_channel[i].get_fds()[j] << std::endl;
					std::cout << msg <<std::endl;
					std::cout << "send :"<<send(_channel[i].get_fds()[j], msg.c_str(), msg.size(), 0) << std::endl;
				}
			}
		}
	}
}