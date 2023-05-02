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
#include <string>
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
#include <stdio.h>
#include <stdlib.h>
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
		struct sockaddr_in					get_addr;
		struct sockaddr_in					send_addr;
		std::map<int, User>&				users;
		std::vector<pollfd>					&fds;
		std::map<int, std::string>			files;
		std::string							_file_name;
		std::string							_file_data;
		std::string							_file_size;

	public:
		File(std::map<int, User> &_users, std::vector<pollfd> &_fds);
		~File();

		void	do_connect();
		void	init_file_data();
		void	send_file(std::string target);
		void	create_file();
		void	execute(std::vector<std::string>& args, int fd);
		User	&find_user(std::string _nick);
};

#endif