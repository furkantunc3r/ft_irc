#include "../includes/dcc.hpp"

Dcc::Dcc(std::map<int, User>& _users)
{
	(void)_users;
	memset(&this->addr, 0, sizeof(this->addr));
	waiting = 1;
}

Dcc::~Dcc(){}

void Dcc::create_socket()
{
	int optval = 1;

	// if (setsockopt(this->listen_fd, SOL_SOCKET, SO_REUSEADDR , &optval, sizeof(optval)) < 0)
	// 	error("setsockopt() failed ", this->listen_fd);
	// if (setsockopt(this->listen_fd, IPPROTO_TCP, TCP_NODELAY , &optval, sizeof(optval)) < 0)
	// 	error("setsockopt() failed ", this->listen_fd);
	// if (bind(this->listen_fd, (struct sockaddr *)&addr, sizeof(addr)))
	// 	error("bind() failed ", this->listen_fd);
	// if (fcntl(this->listen_fd, F_SETFL, O_NONBLOCK) < 0)
	// 	error("fcnt() failed ", this->listen_fd);
}

// void Dcc::do_listen(int fd, size_t listen_count)
// {
// 	if (listen(fd, listen_count) < 0)
// 		error("listen() failed ", this->listen_fd);
// 	// this->fds.push_back((pollfd){listen_fd, POLLIN, 0});
// }

void	Dcc::set_addr(std::string ip, std::string port){
	memset(&this->addr, 0, sizeof(this->addr));
	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = inet_addr(ip.c_str());
	this->addr.sin_port = htons(std::atoi(port.c_str()));
	this->listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listen_fd < 0)
		error("socket () failed ", this->listen_fd);
}

void	Dcc::dcc_send(const std::vector<std::string> &args){
	set_addr(args[3], args[4]);
	// create_socket();
	std::cout << "burda\n";
}
void	Dcc::dcc_accept(const std::vector<std::string> &args){
	(void)args;
	std::cout << "aaaaa\n";
	if (connect(this->listen_fd, (struct sockaddr *)&this->addr, sizeof(this->addr)) < 0)
		error("Connect", this->listen_fd);
	close(listen_fd);
}
void	Dcc::dcc_reject(const std::vector<std::string> &args){(void)args;}

void	Dcc::execute(const std::vector<std::string> &args)
{
	// for(size_t i = 0; i < args.size(); i++)
	// 	std::cout << args[i] << std::endl;
	// dcc_accept(args);
	set_addr(args[3], args[4]);
	// this->execute(parse(buffer, " :"));
}