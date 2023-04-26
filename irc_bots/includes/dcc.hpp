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
		// std::string					ip;
		// int							port;
		int							waiting;
		int							listen_fd;
		// int							new_fd;
		struct sockaddr_in			addr;
		// std::vector<pollfd>			fds;
		std::multimap<std::string, int>	files;
		// std::map<int, User>&		users;
	public:
		Dcc(std::map<int, User>& _users);
		~Dcc();

		void	create_socket();
		void	do_listen(int fd, size_t listen_count);
		void	dcc_send(const std::vector<std::string> &args);
		void	dcc_accept(const std::vector<std::string> &args);
		void	dcc_reject(const std::vector<std::string> &args);
		// void	dcc_checksum(const std::vector<std::string> &args);ma
		void	set_addr(std::string ip, std::string port);
		void	execute(const std::vector<std::string>& args);
		// void	do_recv(pollfd _fds);
		// void	do_accept();
		// void	loop();
};

#endif