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
#include "../../channel/includes/channel.hpp"
#include "../../utils/utils.hpp"
#include <map>
#include <cctype>
#include "../../methods/includes/wohis.hpp"
#include "../../methods/includes/join.hpp"

class Server{

	private:
		int									port;
		int									listen_fd;
		int									new_fd;
		char								buffer[4096];
		std::string							msg;
		struct sockaddr_in					addr;
		std::vector<pollfd>					fds;
		std::vector<Channel>				channels;

		//User								users;
		//Channel							channel;
		std::map<std::string, IMethod*>	method;

	public:
		Server(char* arg);
		~Server();

		void	create_socket();
		void	do_listen(int fd, size_t listen_count);
		void	do_send(int fd);
		void	do_recv(pollfd _fds);
		void	do_accept();
		void	create_channel(std::string name);
		void	create_channel(std::string name, std::string password);
		void	loop();
};

#endif