#include "../includes/server.hpp"

Server::Server(char *arg) : port(atoi(arg)), fds(), new_fd(-1), listen_fd(-1), msg()
{
	this->method["WHOIS"] = new Whois();
	this->method["JOIN"] = new Join();
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
	if (bind(this->listen_fd, (struct sockaddr *)&addr, sizeof(addr)))
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
	
	memset(buffer, 0, 4096);
	rc = recv(_fds.fd, buffer, sizeof(buffer), 0);
	if (rc == 0)
		printf("  Connection closed\n");
	this->msg.assign(buffer);
	printf("  %d bytes received %s\n", rc, msg.c_str());
	std::vector<std::string> a = parse(buffer, " \r\n");
	// std::transform(a[0].begin(), a[0].end(), a[0].begin(), toupper);
	for (size_t i = 0; i < a.size(); i++)
		std::cout << ">" << a[i] << "<" << std::endl;
	std::map<std::string, IMethod*>::iterator it = this->method.find(a[0]);
	if (it != this->method.end())
		it->second->do_method(a, _fds.fd);
	else
		this->create_user(a);
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
	int	rc = 0;
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
					for (size_t j = 1; j < fds.size(); j++)
						this->do_send(fds[j].fd);
					
				}
			}
		}
	}
}

void Server::create_channel(std::string name)
{
	// this->channels.push_back(Channel(name, this->new_fd));
}

void Server::create_user(std::vector<std::string> info)
{
	User usr()
}