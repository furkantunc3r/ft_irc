#ifndef DCC_HPP
#define DCC_HPP

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "../../utils/utils.hpp"
#include "../../user/includes/user.hpp"
#include <stdlib.h>

#define SEND "SEND"
#define GET "GET"
#define REJECT "REJECT"

class Dcc {
	private:
		int							listen_fd;
		struct sockaddr_in			addr;

	public:
		Dcc();
		~Dcc();
		void	execute(const std::vector<std::string>& args);
};

#endif