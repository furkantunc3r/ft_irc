#include "../includes/server.hpp"

Server::Server(char *arg, char *pass) : port(atoi(arg)), fds(), new_fd(-1), listen_fd(-1), _pass(pass)
{
	memset((char *)&this->addr, 0, sizeof(this->addr));

	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = INADDR_ANY;
	this->addr.sin_port = htons(this->port);

	this->method["WHOIS"] = new Whois();
	this->method["JOIN"] = new Join(this->users, this->channels);
	this->method["CAP"] = new Cap(this->users, *this);
	this->method["PRIVMSG"] = new Message(this->users, this->channels);
	this->method["QUIT"] = new Quit(this->users, this->fds, this->channels);
	this->method["PASS"] = new Pass(this->users);
}

Server::~Server() {
	std::map<std::string, IMethod*>::iterator it = this->method.begin();
	for (; it != this->method.end(); it++)
		delete it->second;
}

void Server::create_socket()
{
	int buf_size = 0;
	
	this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listen_fd < 0)
		error("socket () failed ", this->listen_fd);
	if (setsockopt(this->listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&buf_size, sizeof(buf_size)) < 0)
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

void Server::do_recv(pollfd _fds)
{
	int rc = 0;
	char *buffer = new char[100];
	int i = 0;
	while(!strstr(buffer, "\r\n"))
	{
		i++;
		memset(buffer, 0, 100);
		rc = recv(_fds.fd, buffer, 100, 0);
		if (rc == -1)
		{
			std::cout << "  Connection closed" << std::endl;
			std::vector<pollfd>::iterator it = this->fds.begin();
			for(; it->fd != _fds.fd; it++) {}
			this->fds.erase(it);
			close(_fds.fd);
			exit(1);
		}
		msg.append(buffer);
	}
	sleep(2);
	if (rc > 0)
	{
		std::cout << "------------------" << std::endl;
		std::cout << "recv : " << msg << std::endl;
		std::cout << "------------------" << std::endl;
		std::vector<std::string> first = parse(msg, ":");
		std::vector<std::string> second = parse(first[0], " \r\n");

		if (first.size() > 1)
			second.push_back(first.back());
		std::transform(second[0].begin(), second[0].end(), second[0].begin(), toupper);
		for (size_t i = 0; i < second.size(); i++)
			std::cout << "second : "<<second[i] << std::endl;
		// std::map<std::string, IMethod *>::iterator it = this->method.find(second[0]);
		// if (it != this->method.end())
		// 	it->second->execute(second, _fds.fd);
	}
	delete buffer;
	msg.clear();
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

void Server::print_users()
{
	std::map<int, User>::iterator it = this->users.begin();

	for(; it != this->users.end(); it++)
		std::cout << "Username: " << it->second._nickname << " " << "Connected fd: " << it->second._fd << std::endl;

	// for (size_t i = 0; i < this->users.size(); i++)
	// 	std::cout << "Username: " << this->users[i]._nickname << " "
	// 			  << "Connected fd: " << this->users[i]._fd << std::endl;
}

std::string Server::get_pass()
{
	return this->_pass;
}