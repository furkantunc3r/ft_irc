#ifndef SERVER_HPP
#define SERVER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <algorithm>

class Server{

	private:
		int									port;
		int									listen_fd;
		int									new_fd;
		char								buffer[4096];
		std::string							msg;
		struct sockaddr_in					addr;
		std::vector<pollfd>					fds;
		//User								users;
		//Channel							channel;
		//std::map<std::string, Method*>	method;

	public:
		Server(char* arg);
		~Server();

		void	create_socket();
		void	do_listen(int fd, size_t listen_count);
		void	do_send(int fd);
		void	do_recv(pollfd _fds);
		void	do_accept();
		void	loop();
};

#endif