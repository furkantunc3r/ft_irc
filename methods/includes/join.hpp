#ifndef JOIN_HPP
#define JOIN_HPP

#include "imethod.hpp"

class Join : public IMethod{
	public:
		Join();
		~Join();
		void	do_method(std::vector<std::string> arg, int fd);
};

#endif
