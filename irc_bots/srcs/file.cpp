#include "../includes/file.hpp"

std::string sha;
File::File(std::map<int, User> &_users, std::vector<pollfd> &_fds) : users(_users), fds(_fds), new_fd(-1)
{(void)fds;}


File::~File() {}

void File::do_connect()
{
	if (connect(this->send_fd, (struct sockaddr *)&send_addr, sizeof(send_addr)) < 0)
		perror("connect ");
}

void File::init_file_data()
{
	char *buffer = new char[SIZE];

	memset(buffer, 0, SIZE);
	while (_file_data.size() < (size_t)atoi(_file_size.c_str()))
	{
		if (recv(send_fd, buffer, SIZE, 0) < 0)
		{
			perror("recv ");
			return;
		}
		_file_data.append(buffer);
		memset(buffer, 0, SIZE);
	}
	if (_file_data.size() == (size_t)atoi(_file_size.c_str()))
	{
		std::cout << "tamamlandı" << std::endl;
		std::string msg(":NOTICE acetin1 :DCC SEND 'a.txt' to file completed\r\n");
		if (send(send_fd, msg.c_str(), msg.size(), 0) < 0)
			perror("send ");
	}
	_file_data.append("\n/* ************************************************************************** */\n");
	_file_data.append("/*                                                                            */\n");
	_file_data.append("/*                                                        :::      ::::::::   */\n");
	_file_data.append("/*   ft_irc.c			                               :+:      :+:    :+:   */\n");
	_file_data.append("/*                                                    +:+ +:+         +:+     */\n");
	_file_data.append("/*   By: acetin <acetin@42.fr>                      +#+  +:+       +#+        */\n");
	_file_data.append("/*                                                +#+#+#+#+#+   +#+           */\n");
	_file_data.append("/*         										      #+#    #+#             */\n");
	_file_data.append("/*   									             ###   ########.fr       */\n");
	_file_data.append("/*                                                                            */\n");
	_file_data.append("/* ************************************************************************** */\n");
	std::cout << _file_data << std::endl;
}

void File::create_file()
{
	std::ofstream _file;
	_file.open("files/" + _file_name, std::iostream::trunc);
	if (!_file.is_open())
		perror("File ");
	_file << _file_data;
	_file.close();
}


void File::send_file(std::string target)
{
	(void)target;
	memset(&this->get_addr, 0, sizeof(this->get_addr));
	this->get_fd = socket(AF_INET, SOCK_STREAM, 0);
	this->get_addr.sin_family = AF_INET;
	this->get_addr.sin_addr.s_addr = INADDR_ANY; //(inet_addr("2130706433"));
	this->get_addr.sin_port = htons(8080);
	struct timeval tv;
	tv.tv_sec = 10; // 10 saniye
	tv.tv_usec = 0;
	// if (fcntl(this->get_fd, F_SETFL, O_NONBLOCK) < 0)
	// 	perror("fcnt() failed ");
	if (setsockopt(get_fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv) < 0)
		perror("setsock");
	bind(this->get_fd, (struct sockaddr *)&get_addr, sizeof(get_addr));
	listen(get_fd, 5);
	// this->fds.push_back((pollfd){get_fd, POLLIN, 0});
	// IPv4 adresi = a x (256^3) + b x (256^2) + c x (256) + d ıp sayısal formatı
	new_fd = -1;
	new_fd = accept(get_fd, NULL, NULL);
	// fds.push_back((pollfd){get_fd, POLLIN, 0});
	// std::cout << new_fd << std::endl;
}

User &File::find_user(std::string _nick)
{
	std::map<int, User>::iterator it = this->users.begin();
	for (; it != users.end(); it++)
	{
		if (it->second._nickname == _nick)
			break;
	}
	return it->second;
}

void File::execute(std::vector<std::string> &args, int fd)
{
	(void)fd;
	if (args[0] == "SHA-256")
		return;
	_file_size = args[5];
	if (atoi(_file_size.c_str()) > 5000 || args[2].find(".txt") == args[2].npos)
	{
		std::cout << "burada\n";
		std::string msg(":NOTICE acetin1 :DCC SEND 'a.txt' to file aborted\r\n");
		if (send(send_fd, msg.c_str(), msg.size(), 0) < 0)
			return;
	}
	if (_file_data.empty())
	{
		memset(&this->send_addr, 0, sizeof(this->send_addr));
		this->send_fd = socket(AF_INET, SOCK_STREAM, 0);
		this->send_addr.sin_family = AF_INET;
		this->send_addr.sin_addr.s_addr = (inet_addr(args[3].c_str()));
		this->send_addr.sin_port = htons(atoi(args[4].c_str()));
		_file_name = "ft_" + args[2];
		std::cout << inet_ntoa(send_addr.sin_addr) << " " << args[4] << std::endl;
		do_connect();
		init_file_data();
		create_file();
	}
	if (!_file_data.empty())
	{
		//NON BLOCKING OLMADI
 		// send_file(*(args.end() - 1));
		// std::string msg(this->users.find(-3)->second._prefix + "PRIVMSG " + *(args.end() - 1) + " :" + '\x01' + "DCC SEND " + _file_name + " 2130706433 8080 " + _file_size + '\x01' + "\r\n");
		// std::cout << msg << std::endl;
		// send(find_user(*(args.end() - 1))._fd, msg.c_str(), msg.size(), 0);
		// send(new_fd, _file_data.c_str(), _file_data.size(), 0);
		// // close(get_fd);
		// _file_data.clear();
	}
}