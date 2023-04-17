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
#include "../../methods/includes/cap.hpp"
#include "../../methods/includes/message.hpp"
#include "../../methods/includes/quit.hpp"
#include "../../methods/includes/pass.hpp"
#include "../../methods/includes/nick.hpp"

class Server{

	private:
		int									port;
		int									listen_fd;
		int									new_fd;
		char								buffer[4096];
		struct sockaddr_in					addr;
		std::vector<pollfd>					fds;

		std::map<int, User>					users;
		std::map<std::string, Channel>		channels;
		std::map<std::string, IMethod*>		method;

		std::string							_pass;

	public:
		Server(char* arg, char *pass);
		~Server();

		void	create_socket();
		void	do_listen(int fd, size_t listen_count);
		void	do_send(int fd);
		void	do_recv(pollfd _fds);
		void	do_accept();
		void 	create_user(std::vector<std::string> info, int fd);
		void	create_channel(std::string name);
		void	create_channel(std::string name, std::string password);
		void	print_users();
		void	loop();

		std::string	get_pass();
};

#endif