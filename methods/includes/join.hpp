#ifndef JOIN_HPP
#define JOIN_HPP

#include "imethod.hpp"
#include "../../channel/includes/channel.hpp"
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

class Join : public IMethod{
	public:
		Join();
		~Join();
		void	do_method(std::vector<std::string> &arg, int fd);
};

#endif
