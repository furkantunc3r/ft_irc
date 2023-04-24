#ifndef SERVER_HPP
#define SERVER_HPP

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
#include "../../channel/includes/channel.hpp"
#include "../../utils/utils.hpp"
#include <map>
#include <cctype>
#include "../../methods/includes/join.hpp"
#include "../../methods/includes/cap.hpp"
// #include "../../methods/includes/message.hpp"
#include "../../methods/includes/quit.hpp"
#include "../../methods/includes/pass.hpp"
#include "../../methods/includes/nick.hpp"
#include "../../methods/includes/usercmd.hpp"
#include "../../methods/includes/privmsg.hpp"
#include "../../methods/includes/oper.hpp"
#include "../../methods/includes/kick.hpp"
#include "../../methods/includes/ping.hpp"
#include "../../methods/includes/part.hpp"

class Server{

	private:
		int									port;
		int									listen_fd;
		int									new_fd;
		std::string							msg;
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
		void	do_recv(pollfd _fds);
		void	do_accept();
		void	execute(std::string, int fd);
		void	print_users();
		void	loop();

		int		get_user_fd_if_on_server(std::string name);
		User&	get_user(int fd);

		Channel&	get_channel(std::string name);
		bool		search_channel(std::string name);

		std::string	get_pass();
		void	erase_user(int fd);
		void	erase_channel(std::string channel);
};

#endif