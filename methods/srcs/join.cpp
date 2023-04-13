#include "../includes/join.hpp"

Join::Join(std::vector<User>& users, std::vector<Channel>& channel) : _users(users), _channel(channel) {}

Join::~Join(){}

void Join::execute(std::vector<std::string> &arg, int fd)
{
	if (does_exist_channel(this->_channel, arg.back(), fd))
		this->_channel.push_back(Channel(fd, arg.back()));
	if (!does_exist_channel(this->_channel, arg.back(), fd))
	{
		std::cout << this->_channel.size() << std::endl;
		std::string nick;
		std::cout << "user size : " << this->_users.size() << std::endl;
		for (size_t i = 0; i < _users.size(); i++)
		{
			if (_users[i]._fd == fd)
			{
				nick = _users[i]._nickname;
				for (size_t j = 0; j < this->_channel.size(); j++)
				{
					if (!strncmp(this->_channel[j].get_name().c_str(), arg[2].c_str(), this->_channel[j].get_name().size()))
					{
						std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
						this->_channel[j].add_user(fd);
					}
				}
			}
		}
		for (size_t i = 0; i < this->_channel[0].get_fds().size(); i++)
		{
			std::cout << this->_channel[0].get_fds()[i] << std::endl;
		}
		
		std::string a(":"  + nick + "!localhost JOIN ");
		a.append(arg.back() + "\r\n");
		std::cout << "******************************" << std::endl;
		std::cout << a << std::endl;
		std::cout << "******************************" << std::endl;
		send(fd, a.c_str(), a.length(), 0);
	}
}