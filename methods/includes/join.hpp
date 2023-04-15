#ifndef JOIN_HPP
#define JOIN_HPP

#include "imethod.hpp"
#include "../../channel/includes/channel.hpp"
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include "../../user/includes/user.hpp"
#include "../../channel/includes/channel.hpp"
#include <map>

class Join : public IMethod{
	std::map<int, User>&			_users;
	std::map<std::string, Channel>&	_channels;
	
	// std::vector<User>&		_users;
	// std::vector<Channel>&	_channel;
	public:
		Join(std::map<int, User> &users, std::map<std::string, Channel> &channel);
		~Join();
		void	execute(std::vector<std::string> &arg, int fd);
};

#endif
