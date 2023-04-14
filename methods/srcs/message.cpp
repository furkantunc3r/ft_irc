#include "../includes/message.hpp"

Message::Message(std::map<std::string, Channel>& channel) : _channels(channel){}

Message::~Message(){}

void Message::execute(std::vector<std::string> &arg, int fd){
	std::cout << "ANAN!!!!" << std::endl;
	std::string msg;
	std::cout << "SAAS!!!!" << std::endl;
	msg.append(":acetin1!Abdullah1@localhost "); //dinamik yap
	msg.append("PRIVMSG " + arg[2] + " :");
	for (size_t i = 4; i < arg.size(); i++)
		msg.append(trim(arg[i], ':'));
	msg.append("\r\n");

	std::map<std::string, Channel>::iterator it = this->_channels.begin();
	std::map<std::string, Channel>::iterator ite = this->_channels.begin();
	if (!channel_validate(this->_channels, arg[2], fd))
	{
		for (size_t i = 0; it != this->_channels.end(); it++, i++)
		{
			std::cout << "channel size : "<<this->_channels.size() << std::endl;
			if(!strncmp(it->second.get_name().c_str(), arg[2].c_str(), it->second.get_name().size()))
			{
				std::cout << "aaaaaaaaaaaaaaaa\n";
				char buffer[4096];
				for (size_t j = 0; j < it->second.get_fds().size(); ite++, j++)
				{
					std::cout << "fd : "<< ite->second.get_fds()[j] << std::endl;
					std::cout << msg <<std::endl;
					std::cout << "send :"<< send(it->second.get_fds()[j], msg.c_str(), msg.size(), 0) << std::endl;
				}
			}
		}


		// for (size_t i = 0; i < this->_channel.size(); i++)
		// {
		// 	std::cout << "channle size : "<<this->_channel.size() << std::endl;
		// 	if(!strncmp(_channel[i].get_name().c_str(), arg[2].c_str(), _channel[i].get_name().size()))
		// 	{
		// 		std::cout << "aaaaaaaaaaaaaaaa\n";
		// 		char buffer[4096];
		// 		for (size_t j = 0; j < _channel[i].get_fds().size(); j++)
		// 		{
		// 			std::cout << "fd : "<<_channel[i].get_fds()[j] << std::endl;
		// 			std::cout << msg <<std::endl;
		// 			std::cout << "send :"<<send(_channel[i].get_fds()[j], msg.c_str(), msg.size(), 0) << std::endl;
		// 		}
		// 	}
		// }
	}
}