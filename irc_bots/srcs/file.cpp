#include "../includes/file.hpp"

File::File(std::map<int, User> &_users) : users(_users)
{
	int optval = 1;
	
	memset(&this->addr, 0, sizeof(this->addr));
	
	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = INADDR_ANY;
	this->addr.sin_port = htons(4445);
	this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	this->create_socket();
	this->do_listen(this->listen_fd, 10);
}

File::~File(){}

void File::create_socket()
{
	int optval = 1;

	this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listen_fd < 0)
		error("socket () failed ", this->listen_fd);
	if (setsockopt(this->listen_fd, SOL_SOCKET, SO_REUSEADDR , &optval, sizeof(optval)) < 0)
		error("setsockopt() failed ", this->listen_fd);
	// if (setsockopt(this->listen_fd, IPPROTO_TCP, TCP_NODELAY , &optval, sizeof(optval)) < 0)
	// 	error("setsockopt() failed ", this->listen_fd);
	if (fcntl(this->listen_fd, F_SETFL, O_NONBLOCK) < 0)
		error("fcnt() failed ", this->listen_fd);
	if (bind(this->listen_fd, (struct sockaddr *)&addr, sizeof(addr)))
		error("bind() failed ", this->listen_fd);
}

void File::do_listen(int fd, size_t listen_count)
{
	if (listen(fd, listen_count) < 0)
	{
		error("listen() failed ", this->listen_fd);
		return ;
	}
	this->fds.push_back((pollfd){fd, POLLIN, 0});
}

void File::do_accept(int fd)
{
	this->new_fd = accept(this->listen_fd, NULL, NULL);
	if (new_fd < 0)
		perror("accept ");
	this->fds.push_back((pollfd){new_fd, POLLIN, 0});
}

void File::send_file(User user, std::vector<std::string> &args)
{
	std::ifstream _file;
	size_t len = 0;
	std::vector<std::string> temp;

	temp = parse(args[3], "/");
	// std::pair<User, std::string>   p( user, temp.back());
	// this->files.insert(std::pair<User, std::string>(user, temp.back()));
	std::cout << args[3] << std::endl;
	_file.open(args[3]);
	if (!_file.is_open())
		perror("File ");
	std::string data((std::istreambuf_iterator<char>(_file)), (std::istreambuf_iterator<char>()));
	_file.close();
	std::string _size(std::to_string(data.size()) + "\r\n");
	
	if(send(new_fd, _size.c_str(), _size.size(), 0) < 0)
	{
		perror(std::string("send file " + std::to_string(new_fd) + " ").c_str());
		return;
	}
	while(len < data.size())
	{
		if (send(new_fd, data.c_str(), 512, 0) < 0)
		{
			perror(std::string("send1 file " + std::to_string(new_fd) + " ").c_str());
			break;
		}
		len += 512;
	}
	std::cout << "gitti" << std::endl;
}

void File::get_file(User user, std::vector<std::string> &args)
{
	std::ofstream _file;
	std::string data;
	char buffer[512];
	size_t len = 0;
	size_t _size = 0;
	std::vector<std::string> temp;
	// std::multimap<User, std::string>::iterator it  = this->files.begin();
	memset(buffer, 0, sizeof(buffer));
	// s
	_file.open(args[3], std::iostream::trunc);
	if (!_file.is_open())
		perror("File :");
	if(recv(listen_fd, buffer, sizeof(buffer), 0) < 0)
	{
			perror("get file : ");
			return;
	}
	temp = parse(buffer, "\r\n");
	_size = atoi(temp[0].c_str());
	data.append(temp[1]);
	while(len < _size)
	{
		if (recv(listen_fd, buffer, sizeof(buffer), 0) < 0)
		{
			perror("get file : ");
			break;
		}
		data.append(buffer);
		len += sizeof(buffer);
		memset(buffer, 0, sizeof(buffer));
	}
	std::cout << "geldi" << std::endl;
	_file.close();
}

void	File::execute(std::vector<std::string> &args, int fd)
{
	
	std::transform(args[1].begin(), args[1].end(), args[1].begin(), ::toupper);
	
	// if (poll(fds.begin().base(), fds.size(), -1) < 0)
	// 	return ;
	for (size_t i = 0; i < fds.size(); i++)
	{
		// if (fds[i].revents & POLLIN)
		{
			if (fds[i].fd == listen_fd)
				do_accept(fd);
			if (args[1] == "SEND")
				send_file(this->users.find(fd)->second, args);
			else if(args[1] == "GET")
				send_file(this->users.find(fd)->second, args);
		}
		std::cout << "aaaaa\n";
	}
	for(std::vector<pollfd>::iterator i = fds.begin(); i != fds.end(); i++)
	{
		if ((*i).fd == fd)
		{
			fds.erase(i);
			break;
		}
	}
	close(listen_fd);
}