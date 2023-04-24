#include "../includes/server.hpp"

Server::Server(char *arg, char *pass) : port(atoi(arg)), fds(), new_fd(-1), listen_fd(-1), _pass(std::string(pass))
{
	memset((char *)&this->addr, 0, sizeof(this->addr));

	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = INADDR_ANY;
	this->addr.sin_port = htons(this->port);

	this->method["JOIN"] = new Join(this->users, this->channels);
	this->method["CAP"] = new Cap(this->users, *this);
	this->method["QUIT"] = new Quit(this->users, this->fds, this->channels);
	this->method["NICK"] = new Nick(this->users);
	this->method["PASS"] = new Pass(this->users, this->_pass);
	this->method["USER"] = new Usercmd(this->users);
	this->method["PRIVMSG"] = new Privmsg(this->users, this->channels);
	this->method["KICK"] = new Kick(*this);
	this->method["PING"] = new Ping(*this);
	this->method["PART"] = new Part(this->channels);
	// this->method["OPER"] = new Oper(this->users, this->_opers, this->_oper_pass);
}

Server::~Server()
{
	std::map<std::string, IMethod *>::iterator it = this->method.begin();
	for (; it != this->method.end(); it++)
		delete it->second;
}

void Server::create_socket()
{
	int optval = 1;

	this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listen_fd < 0)
		error("socket () failed ", this->listen_fd);
	if (setsockopt(this->listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
		error("setsockopt() failed ", this->listen_fd);
	if (fcntl(this->listen_fd, F_SETFL, O_NONBLOCK) < 0)
		error("fcnt() failed ", this->listen_fd);
	if (bind(this->listen_fd, (struct sockaddr *)&addr, sizeof(addr)))
		error("bind() failed ", this->listen_fd);
}

void Server::do_listen(int fd, size_t listen_count)
{
	if (listen(fd, listen_count) < 0)
		error("listen() failed ", this->listen_fd);
	std::cout << "Listen " << this->port << std::endl;
	this->fds.push_back((pollfd){listen_fd, POLLIN, 0});
}


void Server::execute(std::string arg, int fd)
{
	std::vector<std::string> cmd = parse(arg, ":");
	std::vector<std::string> cmd2 = parse(cmd[0], " \r\t\n");
	if (cmd.size() > 1)
		cmd2.push_back(cmd[1]);
	std::map<std::string, IMethod *>::iterator it = this->method.find(cmd2[0]);
	if (it != this->method.end())
		it->second->execute(cmd2, fd);
}
int Server::get_user_fd_if_on_server(std::string name)
{
	std::map<int, User>::iterator it = this->users.begin();

	for (; it != this->users.end(); it++)
	{
		if (it->second._nickname == name)
			return it->second._fd;
	}
	return 0;
}

User& Server::get_user(int fd)
{
	return this->users.find(fd)->second;
}

Channel& Server::get_channel(std::string name)
{
	return this->channels.find(name)->second;
}

bool Server::search_channel(std::string name)
{
	if (this->channels.find(name) != this->channels.end())
		return 1;
	return 0;
}

void Server::do_recv(pollfd _fds)
{
	int rc = 1;
	char *buffer = new char[100];
	memset(buffer, 0, 100);
	rc = recv(_fds.fd, buffer, 100, 0);
	std::cout <<"auuuuuuu " <<buffer << std::endl;
	std::vector<std::string> temp = parse(buffer, "\r\n");
	for (size_t i = 0; i < temp.size(); i++)
		this->execute(temp[i], _fds.fd);
	// std::cout << rc << std::endl;
	if (rc <= 0)
	{
		// perror("recv ()");
		std::cout << "  Connection closed" << std::endl;
		std::vector<pollfd>::iterator it = this->fds.begin();
		for (; it->fd != _fds.fd; it++){}
		this->fds.erase(it);
		close(_fds.fd);
	}
	delete[] buffer;
}

void Server::do_accept()
{
	this->new_fd = accept(this->listen_fd, NULL, NULL);
	this->fds.push_back((pollfd){new_fd, POLLIN, 0});
}

void Server::loop()
{
	int rc = 0;
	this->create_socket();
	this->do_listen(this->listen_fd, 1024);
	while (1)
	{
		if (poll(fds.begin().base(), fds.size(), -1) < 0)
			perror("poll() failed");
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == this->listen_fd)
					this->do_accept();
				else
				{
					this->do_recv(fds[i]);
					this->print_users();
				}
			}
		}
	}
}

void Server::erase_user(int fd)
{
	std::map<int, User>::iterator it = this->users.find(fd);
	if (it != this->users.end())
		this->users.erase(it);
}

void Server::erase_channel(std::string channel)
{
	std::map<std::string, Channel>::iterator it = this->channels.find(channel);
	if (it != this->channels.end())
		this->channels.erase(it);
}

void Server::print_users()
{
	std::map<int, User>::iterator it = this->users.begin();

	for(; it != this->users.end(); it++)
		std::cout << "Username: " << it->second._nickname << " " << "Connected fd: " << it->second._fd << " IS regis: " << it->second._is_regis << std::endl;

	// for (size_t i = 0; i < this->users.size(); i++)
	// 	std::cout << "Username: " << this->users[i]._nickname << " "
	// 			  << "Connected fd: " << this->users[i]._fd << std::endl;
}

std::string Server::get_pass()
{
	return this->_pass;
}