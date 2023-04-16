#include "../includes/leaving_bot.hpp"
#include <vector>
LeavingBot::LeavingBot(std::map<int, User> &users, std::map<std::string, Channel> &channels) : _users(users), _channels(channels), _message(_users, _channels){}

LeavingBot::~LeavingBot(){}

void LeavingBot::send_message(int fd, std::string reason){
	std::map<int, User>::iterator user_it = _users.find(fd);
	
	if (user_it != _users.end())
	{
		for (size_t i = 0 ; i < user_it->second._channels.size(); i++)
		{
			std::string msg;
			msg.append("PRIVMSG " + user_it->second._channels[i] + " "
				+ user_it->second._nickname + " has disconnected from the server =>" + reason +"\r\n");
			std::vector<std::string> temp = parse(msg, " \r\n");
			this->_message.execute(temp, -1);
		}
	}
}