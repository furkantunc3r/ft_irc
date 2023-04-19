#include "../includes/server.hpp"

Server::Server(char *arg, char *pass) : port(atoi(arg)), fds(), new_fd(-1), listen_fd(-1), _pass(std::string(pass)), _oper_pass(std::string("1071"))
{
	memset((char *)&this->addr, 0, sizeof(this->addr));

	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = INADDR_ANY;
	this->addr.sin_port = htons(this->port);

	memset(buffer, 0, 4096);

	this->method["JOIN"] = new Join(this->users, this->channels);
	this->method["CAP"] = new Cap(this->users, *this);
	// this->method["PRIVMSG"] = new Message(this->users, this->channels);
	this->method["QUIT"] = new Quit(this->users, this->fds, this->channels);
	this->method["NICK"] = new Nick(this->users);
	this->method["PASS"] = new Pass(this->users, this->_pass);
	this->method["USER"] = new Usercmd(this->users);
	this->method["PRIVMSG"] = new Privmsg(this->users, this->channels);
	this->method["OPER"] = new Oper(this->users, this->_opers, this->_oper_pass);
}

Server::~Server() {
	std::map<std::string, IMethod*>::iterator it = this->method.begin();
	for (; it != this->method.end(); it++)
		delete it->second;
}

void Server::create_socket()
{
	int on;
	this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listen_fd < 0)
		error("socket () failed ", this->listen_fd);
	if (setsockopt(this->listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
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
	int rc;

	memset(buffer, 0, 4096);
	rc = recv(_fds.fd, buffer, sizeof(buffer), 0);
	if (rc == 0)
	{
		std::cout << "  Connection closed" << std::endl;
		// compress_array(this->fds);
	}
	if (rc > 0)
	{
		std::cout << rc <<" bytes received " << buffer << std::endl;
		std::vector<std::string> a = parse(buffer, " \r\n");
		std::vector<std::string> b;

		// std::transform(a[0].begin(), a[0].end(), a[0].begin(), toupper);
		// for (size_t i = 0; i < a.size(); i++)
		// 	std::cout << ">" <<a[i] << "<" << std::endl;

		for (size_t i = 0; i < a.size(); i++)
		{
			std::map<std::string, IMethod *>::iterator it = this->method.find(a[i]);
			if (it != this->method.end())
			{
				std::map<std::string, IMethod *>::iterator ite;
				int j = i + 1;
				b.insert(b.end(), a[i]);
				for (; j < a.size(); j++)
				{
					ite = this->method.find(a[j]);
					if (ite == this->method.end())
						b.insert(b.end(), a[j]);
					else
						break ;
					
				}
				it->second->execute(b, _fds.fd);
				b.clear();
			}
		}
		if (this->users.find(_fds.fd)->second._joinable == -1)
			this->users.erase(_fds.fd);
	}
}

void Server::do_send(int fd)
{
	if (send(fd, buffer, strlen(buffer), 0) < 0)
		perror("send() failed");
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
		std::cout << "Username: " << it->second._nickname << " " << "Connected fd: " << it->second._fd << " IS regis: " << it->second._is_regis << " Role: " << it->second._role << std::endl;

	// for (size_t i = 0; i < this->users.size(); i++)
	// 	std::cout << "Username: " << this->users[i]._nickname << " "
	// 			  << "Connected fd: " << this->users[i]._fd << std::endl;
}

std::string Server::get_pass()
{
	return this->_pass;
}