#ifndef CAP_HPP
#define CAP_HPP

#include "imethod.hpp"
#include "../../user/includes/user.hpp"
class Cap :public IMethod{

	private:
		std::vector<User>&	_users;
	public:
		Cap(std::vector<User>&	users);
		~Cap();
		void execute(std::vector<std::string> &arg, int fd);
};

#endif