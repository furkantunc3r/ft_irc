#include "../includes/join.hpp"

Join::Join(std::map<int, User> &users, std::map<std::string, Channel> &channel) : _users(users), _channels(channel) {}

Join::~Join() {}

void Join::execute(std::vector<std::string> &arg, int fd)
{
	std::cout << ">JOIN TEST<\n";
	for (size_t i = 0; i < arg.size(); i++)
		std::cout << "---->ARG " << i << " " << arg[i] << "<----\n";

	if (arg[1][0] != '#' || !arg[1][1])
	{
		send(fd, "Channel name has to start with #\r\n", 34, 0);
		return;
	}

	if (channel_validate(this->_channels, arg.back(), fd))
	{
		Channel cha(fd, arg.back(), this->_users);
		
		cha.make_admin(fd);
		this->_channels.insert(std::make_pair(arg.back(), cha));
	}
	
	if (!channel_validate(this->_channels, arg.back(), fd))
	{
		std::cout << this->_channels.size() << std::endl;
		std::string nick;
		std::string username;
		std::map<std::string, Channel>::iterator channel_it = this->_channels.find(arg[1]);
		std::map<int, User>::iterator user_it = this->_users.find(fd);
		if (user_it != this->_users.end())
		{
			nick = user_it->second._nickname;
			username = user_it->second._username;
			if (channel_it != this->_channels.end())
			{
				channel_it->second.add_user(fd);
				user_it->second._channels.push_back(channel_it->second.get_name());
			}
		}
		std::string a(":" + nick + "!localhost JOIN ");
		a.append(arg.back() + "\r\n");
		send(fd, a.c_str(), a.length(), 0);
	}
}