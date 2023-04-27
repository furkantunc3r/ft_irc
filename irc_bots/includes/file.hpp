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

class File : public IMethod {
	private:
		int									listen_fd;
		struct sockaddr_in					addr;
		std::map<int, User>&				users;
		std::vector<pollfd>					fds;
		// std::map<int, std::string>			files;
		int									new_fd;

	public:
		File(std::map<int, User> &_users);
		~File();
		
		void	create_socket();
		void	do_listen(int fd, size_t listen_count);
		void	do_accept(int fd);
		void	send_file(User user, std::vector<std::string> &args);
		void	get_file(User user, std::vector<std::string> &args);
		void	execute(std::vector<std::string>& args, int fd);
};

#endif