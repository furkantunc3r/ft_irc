#ifndef CAP_HPP
#define CAP_HPP

#include "imethod.hpp"
#include "../../user/includes/user.hpp"
#include "../../irc_bots/includes/leaving_bot.hpp"
#include "../../server/includes/server.hpp"

class Server;

class Cap :public IMethod{

	private:
		std::map<int, User>&	_users;
	public:
		Cap(std::map<int, User>&	users);
		~Cap();
		void execute(std::vector<std::string> &arg, int fd);
};

#endif