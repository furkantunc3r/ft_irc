#include "../includes/server.hpp"

Server::Server(char *arg) : port(atoi(arg)), fds(), new_fd(-1), listen_fd(-1), msg()
{
	memset((char *)&this->addr, 0, sizeof(this->addr));
	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = INADDR_ANY;
	this->addr.sin_port = htons(this->port);
	memset(buffer, 0, 4096);
}

Server::~Server() {}

void Server::create_socket()
{
	int on;
	this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listen_fd < 0)
	{
		perror("socket () failed ");
		close(this->listen_fd);
		exit(EXIT_FAILURE);
	}
	if (setsockopt(this->listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
	{
		perror("setsockopt() failed ");
		close(this->listen_fd);
		exit(EXIT_FAILURE);
	}
	if (fcntl(this->listen_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("fcnt() failed ");
		close(this->listen_fd);
		exit(EXIT_FAILURE);
	}
	if (bind(this->listen_fd, (struct sockaddr *)&this->addr, sizeof(this->addr)))
	{
		perror("bind() failed ");
		close(this->listen_fd);
		exit(EXIT_FAILURE);
	}
}

void Server::do_listen(int fd, size_t listen_count)
{
	if (listen(fd, listen_count) < 0)
	{
		perror("listen() failed ");
		close(this->listen_fd);
		exit(EXIT_FAILURE);
	}
	std::cout << "Listen " << this->port << std::endl;
	this->fds.push_back ((pollfd){listen_fd, POLLIN, 0});
}

void Server::do_recv(pollfd _fds)
{
	int rc;
	char								buffer2[4096];
	
	memset(buffer2, 0, 100);
	rc = recv(_fds.fd, buffer2, sizeof(buffer2), 0);
	if (rc == 0)
		printf("  Connection closed\n");
	this->msg.assign(buffer2);
	printf("  %d bytes received %s\n", rc, msg.c_str());
}

void Server::do_send(int fd)
{
	if (send(fd, msg.c_str(), msg.length(), 0) < 0)
		perror("send() failed");
}

void Server::do_accept(){
	this->new_fd = accept(this->listen_fd, NULL, NULL);
	this->fds.push_back((pollfd){new_fd, POLLIN, 0});
}

void Server::loop(){
	this->create_socket();
	this->do_listen(this->listen_fd, 20);
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
					this->do_send(fds[i].fd);
				}
			}
		}
	}
}

void Server::create_channel(std::string name)
{
	this->channels.push_back(Channel(name, this->new_fd));
}