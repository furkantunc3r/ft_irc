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

	if (channel_validate(this->_channels, arg[1], fd))
	{
		Channel cha(fd, arg[1], this->_users);
		
		std::map<int, User>::iterator user_it = this->_users.find(fd);
		if (user_it != this->_users.end())
		{
			cha.add_user(fd);
			user_it->second._channels.push_back(arg.back());
			std::string a(user_it->second._prefix + "JOIN ");
			a.append(arg.back() + "\r\n");
			send(fd, a.c_str(), a.length(), 0);
		}
		cha.make_admin(fd);
		this->_channels.insert(std::make_pair(arg.back(), cha));
	}
	else if (!channel_validate(this->_channels, arg.back(), fd))
	{
		std::map<std::string, Channel>::iterator channel_it = this->_channels.find(arg[1]);
		std::map<int, User>::iterator user_it = this->_users.find(fd);
		if (user_it != this->_users.end())
		{
			if (channel_it != this->_channels.end())
			{
				channel_it->second.add_user(fd);
				user_it->second._channels.push_back(channel_it->second.get_name());
			}
			std::string a(user_it->second._prefix + "JOIN ");
			a.append(arg[1] + "\r\n");
			send(fd, a.c_str(), a.length(), 0);
		}
	}
}