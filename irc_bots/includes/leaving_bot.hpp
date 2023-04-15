#ifndef LEAVING_BOT_HPP
#define LEAVING_BOT_HPP

#include <iostream>
#include <vector>
#include <map>
#include "../../methods/includes/message.hpp"
#include "../../user/includes/user.hpp"
#include "../../channel/includes/channel.hpp"
#include "../../utils/utils.hpp"

class LeavingBot{
	private:
		std::map<int, User>					&_users;
		std::map<std::string, Channel>		&_channels;
	public:
		Message _message;
		
		LeavingBot(std::map<int, User> &_users, std::map<std::string, Channel> &_channels);
		~LeavingBot();
		
		void send_message(int fd, std::string reason);
};

#endif