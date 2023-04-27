#ifndef FILE_HPP
#define FILE_HPP

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
#include <utility>
#include <vector>
#include <algorithm>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cerrno>
#include "../../utils/utils.hpp"
#include "../../user/includes/user.hpp"
#include "../../methods/includes/imethod.hpp"
#include "../../utils/utils.hpp"

#define SEND "SEND"
#define GET "GET"
#define REJECT "REJECT"

#define SIZE 1024

class File : public IMethod {
	private:
		int									send_fd;
		int									get_fd;
		struct sockaddr_in					send_addr;
		struct sockaddr_in					get_addr;
		std::map<int, User>&				users;
		std::vector<pollfd>					fds;
		std::map<int, std::string>			files;
		int									new_fd;

	public:
		File(std::map<int, User> &_users);
		~File();
		
		void	create_socket(int fd, struct sockaddr_in addr);
		void	do_listen(int fd, size_t listen_count);
		void	do_accept();
		void	do_connect();
		// void	help();
		// void	reject();
		std::string		get_file_data(User user, std::string owner_nick, std::string file);
		std::ofstream	create_file(User user, std::string file);
		int				check_owner(User user, std::string file);
		void			send_file(User user, std::vector<std::string> &args);
		void			get_file(int fd, User user, std::ofstream &_file);
		void			execute(std::vector<std::string>& args, int fd);
};

#endif