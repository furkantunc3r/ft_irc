#include "../includes/cap.hpp"

Cap::Cap(std::map<int, User>&	users) : _users(users){}

Cap::~Cap(){}

void Cap::execute(std::vector<std::string> &arg, int fd){
	bool does_exist = false;
	// trim(arg[4]);

	std::map<int, User>::iterator it = this->_users.begin();
	for (; it != this->_users.end(); it++)
	{
		if (!strncmp(it->second._nickname.c_str(), arg[7].c_str(), it->second._nickname.size()))
			does_exist = true;
	}

	// for (size_t i = 0; i < this->_users.size(); i++)
	// {
	// 	if (!strncmp(this->_users[i]._nickname.c_str(), arg[7].c_str(), this->_users[i]._nickname.size()))
	// 		does_exist = true;
	// }
	
	if (!does_exist)
	{
		User usr(arg[7], arg[10], fd);
		this->_users.insert(std::make_pair(fd, usr));
	}	
}