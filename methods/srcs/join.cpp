#include "../includes/join.hpp"

Join::Join(std::map<int, User> &users, std::map<std::string, Channel> &channel) : _users(users), _channels(channel) {}

Join::~Join(){}

void Join::execute(std::vector<std::string> &arg, int fd)
{
	if (channel_validate(this->_channels, arg.back(), fd))
		this->_channels.insert(std::make_pair(arg.back(), Channel(fd, arg.back())));
	if (!channel_validate(this->_channels, arg.back(), fd))
	{
		std::cout << this->_channels.size() << std::endl;
		std::string nick;
		std::cout << "user size : " << this->_users.size() << std::endl;
		
		std::map<std::string, Channel>::iterator it = this->_channels.begin();
		std::map<int, User>::iterator ite = this->_users.begin();
		for (; ite != this->_users.end(); ite++)
		{
			if (ite->second._fd == fd)
			{
				nick = ite->second._nickname;
				for (; it != this->_channels.end(); it++)
				{
					if (!strncmp(it->second.get_name().c_str(), arg[2].c_str(), it->second.get_name().size()))
					{
						std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
						it->second.add_user(fd);
					}
				}
			}
		}

		it = this->_channels.begin();
		for (size_t i = 0; it != this->_channels.end(); it++, i++)
			std::cout << it->second.get_fds()[i] << std::endl;

		// for (size_t i = 0; i < this->_channel[0].get_fds().size(); i++)
		// {
		// 	std::cout << this->_channel[0].get_fds()[i] << std::endl;
		// }
		
		std::string a(":"  + nick + "!localhost JOIN ");
		a.append(arg.back() + "\r\n");
		std::cout << "******************************" << std::endl;
		std::cout << a << std::endl;
		std::cout << "******************************" << std::endl;
		send(fd, a.c_str(), a.length(), 0);
	}
}