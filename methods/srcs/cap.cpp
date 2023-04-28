#include "../includes/cap.hpp"


Cap::Cap(std::map<int, User> &users) : _users(users)
{
	User _leavingbot("NiGhT_BoT", "irc", -1);
	User _filterbot("FilTer_BoT", "irc", -2);
	this->_users.insert(std::make_pair(-1, _leavingbot));
	this->_users.insert(std::make_pair(-2, _filterbot));
}

Cap::~Cap() {}

void Cap::execute(std::vector<std::string> &arg, int fd)
{
	std::cout << ">CAP TEST<\n";
	
	// bool does_exist = false;

	// if (arg[7] != this->_server.get_pass())
	// {
	// 	std::string msg;
	// 	msg.append(":" + arg[10] + "!" + arg[13] + "localhost" + " 464 " + arg[10] + " :Password incorrect\r\n");
	// 	send(fd, msg.c_str(), msg.size(), 0);
	// 	close(fd);
	// 	return ;
	// }

	// std::map<int, User>::iterator it = this->_users.begin();
	// for (; it != this->_users.end(); it++)
	// {
	// 	if (!strncmp(it->second._nickname.c_str(), arg[10].c_str(), it->second._nickname.size()))
	// 		does_exist = true;
	// }

	// for (size_t i = 0; i < this->_users.size(); i++)
	// {
	// 	if (!strncmp(this->_users[i]._nickname.c_str(), arg[7].c_str(), this->_users[i]._nickname.size()))
	// 		does_exist = true;
	// }
	(void)arg;
	User usr("", "", fd);
	this->_users.insert(std::make_pair(fd, usr));
}