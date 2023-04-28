#include "../includes/file.hpp"

File::File(std::map<int, User> &_users) : users(_users)
{
	int optval = 1;
}

File::~File() {}

void File::do_connect()
{
	if (connect(this->send_fd, (struct sockaddr *)&send_addr, sizeof(send_addr)) < 0)
		perror("connect ");
}

void File::init_file_data()
{
	size_t len = 0;
	char *buffer = new char[SIZE];

	memset(buffer, 0, SIZE);
	while (_file_data.size() < _file_size)
	{
		recv(send_fd, buffer, SIZE, 0);
		_file_data.append(buffer);
		memset(buffer, 0, SIZE);
	}
	std::cout << _file_data << std::endl;
}

void	File::create_file()
{
	std::ofstream _file(_file_name, std::fstream::trunc);
	if (!_file.is_open())
		perror("File ");
	_file << _file_data;
	_file.close();
}

void	File::send_file(std::string target)
{
	//IPv4 adresi = a x (256^3) + b x (256^2) + c x (256) + d ıp sayısal formatı
	std::string msg(this->users.find(-3)->second._prefix + "DCC SEND " + _file_name + " 2130706433 8080 " + std::to_string(_file_size) + "\r\n");
	std::cout << msg << std::endl;
	send(find_user(target)._fd, msg.c_str(), msg.size(), 0);
}

User &File::find_user(std::string _nick)
{
	std::map<int, User>::iterator it = this->users.begin();
	for(; it != users.end(); it++)
	{
		if (it->second._nickname == _nick)
			break;
	}
	return it->second;
}

void File::execute(std::vector<std::string> &args, int fd)
{
	if (args[0] == "SHA-256")
	{	
		std::string msg(this->users.find(-3)->second._prefix + "PRIVMSG " + *(args.end() - 1) + " :SHA-256 checksum for " + _file_name + " (remote): " + *(args.end() - 2) + "\r\n");
		std::cout << msg << std::endl;
		send(find_user(args[1])._fd, msg.c_str(), msg.size(), 0);
		return;
	}
	memset(&this->send_addr, 0, sizeof(this->send_addr));
	_file_data.clear();
	this->send_fd = socket(AF_INET, SOCK_STREAM, 0);
	this->send_addr.sin_family = AF_INET;
	this->send_addr.sin_addr.s_addr = INADDR_ANY;
	this->send_addr.sin_port = htons(atoi(args[4].c_str()));
	_file_size = atoi(args[5].c_str());
	_file_name = "ft_" + args[2];
	do_connect();
	init_file_data();
	create_file();
	send_file(args.back());
	// std::cout << buffer << std::endl;
	
	// std::string msg(this->users.find(-3)->second._prefix + "PRIVMSG " + args.back() + " DCC SEND" + );
	// send()
}