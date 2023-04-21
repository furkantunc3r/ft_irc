#include "../includes/cap.hpp"

Cap::Cap(std::map<int, User> &users, Server &server) : _users(users), _server(server)
{
	User _leavingbot("NiGhT_BoT", "irc", -1);
	this->_users.insert(std::make_pair(-1, _leavingbot));
}

Cap::~Cap() {}

void Cap::execute(std::vector<std::string> &arg, int fd)
{
	bool does_exist = false;

	if (strncmp(_server.get_pass().c_str(), arg[4].c_str(), _server.get_pass().size()))
	{
		std::string msg;
		msg.append(":" + arg[6] + "!" + arg[8] + "localhost" + " 464 " + arg[6] + " :Password incorrect\r\n");
		send(fd, msg.c_str(), msg.size(), 0);
		close(fd);
		return;
	}
	std::cout << arg.size() << std::endl;
	std::map<int, User>::iterator it = this->_users.begin();
	// if (arg.size() > 5)
	{
		std::cout << "aaaaaaaaaaaaaaaaaaaaaaaa\n";
		for (; it != this->_users.end(); it++)
		{
			if (!strncmp(it->second._nickname.c_str(), arg[6].c_str(), it->second._nickname.size()))
				does_exist = true;
		}
		if (!does_exist)
		{
			User usr(arg[6], arg[8], fd);
			this->_users.insert(std::make_pair(fd, usr));
		}
	}
	if (arg.size() < 5)
		close(fd);
}