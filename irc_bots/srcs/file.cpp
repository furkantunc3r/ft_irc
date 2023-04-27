#include "../includes/file.hpp"

File::File(std::map<int, User> &_users) : users(_users)
{
	int optval = 1;

	memset(&this->send_addr, 0, sizeof(this->send_addr));

	this->send_fd = socket(AF_INET, SOCK_STREAM, 0);
	this->send_addr.sin_family = AF_INET;
	this->send_addr.sin_addr.s_addr = INADDR_ANY;
	this->send_addr.sin_port = htons(4445);
	this->create_socket(send_fd, send_addr);

	memset(&this->get_addr, 0, sizeof(this->get_addr));
	this->get_fd = socket(AF_INET, SOCK_STREAM, 0);
	this->get_addr.sin_family = AF_INET;
	this->get_addr.sin_addr.s_addr = INADDR_ANY;
	this->get_addr.sin_port = htons(4445);
	this->create_socket(get_fd, get_addr);
	if (bind(get_fd, (struct sockaddr *)&get_addr, sizeof(get_addr)))
		error("bind() failed ", get_fd);
	if (fcntl(get_fd, F_SETFL, O_NONBLOCK) < 0)
		error("fcnt() failed ", get_fd);
	this->do_listen(get_fd, 10);
}

File::~File() {}

void File::create_socket(int fd, struct sockaddr_in addr)
{
	int optval = 1;

	if (fd < 0)
		error("socket () failed ", fd);
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
		error("setsockopt() failed ", fd);
	if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval)) < 0)
		error("setsockopt() failed ", fd);
}

void File::do_listen(int fd, size_t listen_count)
{
	if (listen(fd, listen_count) < 0)
	{
		error("listen() failed ", this->send_fd);
		return;
	}
	this->fds.push_back((pollfd){fd, POLLIN, 0});
}

void File::do_accept()
{
	this->new_fd = accept(this->get_fd, NULL, NULL);
	if (new_fd < 0)
		perror("accept ");
	this->fds.push_back((pollfd){new_fd, POLLIN, 0});
}

void File::do_connect()
{
	if (connect(this->send_fd, (struct sockaddr *)&send_addr, sizeof(send_addr)) < 0)
		perror("connect ");
}

std::string	 File::get_file_data(User user, std::string owner_nick, std::string file)
{
	std::ifstream _file;
	std::string data;
	_file.open(file);
	if (!_file.is_open())
	{
		std::string msg(user._prefix + " 461 " + user._nickname + " :File not found\r\n");
		send(user._fd, msg.c_str(), msg.size(), 0);
		return data;
	}
	std::map<int, User>::iterator it = users.begin();
	for(; it != users.end(); it++)
	{
		if (it->second._nickname == owner_nick)
			break;
	}
	if (it != users.end())
		this->files.insert(std::make_pair(it->second._fd, parse(file, "/").back()));
	else
	{
		std::string msg(user._prefix + " 461 " + user._nickname + " :user not found\r\n");
		send(user._fd, msg.c_str(), msg.size(), 0);
		return data;
	}
	data.append((std::istreambuf_iterator<char>(_file)), (std::istreambuf_iterator<char>()));
	return data;
}

void File::send_file(User user, std::vector<std::string> &args)
{
	size_t len = 0;
	std::string data;
	std::string msg;
	if (args.size() != 4)
	{
		msg.append(user._prefix + " 461 " + user._nickname + " :Insufficent parameters\r\n");
		send(user._fd, msg.c_str(), msg.size(), 0);
		return;
	}
	if (data.append(get_file_data(user, args[2], args[3])).empty())
		return;
	std::string _size(std::to_string(data.length()) + "\r\n");
	for (std::map<int, User>::iterator it = this->users.begin(); it != this->users.end(); it++)
    {
        if (!strncmp(it->second._nickname.c_str(), args[2].c_str(), it->second._nickname.size()))
        {
			msg.append(user._prefix + "PRIVMSG " + args[2] + " send to "+ parse(args[3], "/").back() + "\r\n");
			std::cout << msg << std::endl;
            send(it->second._fd, msg.c_str(), msg.size(), 0);
            break;;
        }
    }
	msg.clear();
	if (send(send_fd, _size.c_str(), _size.size(), 0) < 0)
	{
		msg.append(user._prefix + " 461 " + user._nickname + " :Failed\r\n");
		send(user._fd, msg.c_str(), msg.size(), 0);
		return;
	}
	while (len < data.size())
	{
		if (send(send_fd, data.c_str() + len, SIZE, 0) < 0)
		{
			perror("send file ");
			break;
		}
		len += SIZE;
	}
	msg.append(user._prefix + " NOTICE " + user._nickname + " : Success\r\n");
	send(user._fd, msg.c_str(), msg.size(), 0);
}

std::ofstream File::create_file(User user, std::string file)
{
	std::ofstream _file;
	
	if (this->files.find(user._fd) == this->files.end())
		return _file;
	std::map<int, std::string>::iterator i = files.begin();
	for (; i != files.end(); i++)
	{
		if (i->second == file)
			break;
	}
	if (i == files.end())
		return _file;
	std::string source("/mnt/c/Users/Abdullah/Desktop/ft_irc/" + file);
	std::cout << source << std::endl;
	_file.open(source, std::iostream::trunc);
	return _file;
}

void File::get_file(int fd, User user,std::ofstream &_file)
{
	std::string data;
	char *buffer = new char[1024];
	size_t len = 0;
	size_t _size = 0;
	std::vector<std::string> temp;
	memset(buffer, 0, sizeof(buffer));
	if(recv(fd, buffer, sizeof(buffer), 0) < 0)
	{
		perror("get file : ");
		return;
	}
	temp = parse(buffer, "\r\n");
	_size = atoi(temp[0].c_str());
	if (temp.size() > 1)
		_file << temp[1];
	memset(buffer, 0, sizeof(buffer));
	while(_file.tellp() < _size)
	{
		if (recv(fd, buffer, _size, 0) < 0)
		{
			perror("get file : ");
			break;
		}
		_file << buffer;
		memset(buffer, 0, sizeof(buffer));
	}
	_file.close();
	close(fd);
	this->files.erase(user._fd);
	std::cout << "geldi\n" << std::endl;
}

void File::execute(std::vector<std::string> &args, int fd)
{
	std::transform(args[1].begin(), args[1].end(), args[1].begin(), ::toupper);
	if (args[1] == "SEND")
	{
		do_connect();
		send_file(this->users.find(fd)->second, args);
	}
	else if (args[1] == "GET")
	{
		if (args.size() != 3)
		{
			std::string msg(this->users.find(fd)->second._prefix + " 461 " + this->users.find(fd)->second._nickname + " :Insufficent parameters\r\n");
			send(this->users.find(fd)->second._fd, msg.c_str(), msg.size(), 0);
			return;
		}
		std::ofstream _file = create_file(this->users.find(fd)->second, args[2]);
		if (!_file.is_open())
		{
			std::string msg(this->users.find(fd)->second._prefix + " 461 " + this->users.find(fd)->second._nickname + " :Something is wrong\r\n");
			send(this->users.find(fd)->second._fd, msg.c_str(), msg.size(), 0);
			return ;
		}
		if (poll(fds.begin().base(), fds.size(), -1) < 0)
			return;
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == get_fd)
					do_accept();
				get_file(new_fd, this->users.find(fd)->second, _file);
			}
		}
		
	}
}