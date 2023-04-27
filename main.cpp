#include "server/includes/server.hpp"
#include <signal.h>
volatile sig_atomic_t signal_received = 1;
void handler(int signal)
{
	(void)signal;
	signal_received = 0;
	
}

void loop(Server *server){
	std::vector<pollfd>	_fds;

	while (signal_received)
	{
		_fds = server->get_fds();
		if (poll(_fds.begin().base(), _fds.size(), -1) < 0)
			break;
		for (size_t i = 0; i < _fds.size(); i++)
		{
			if (_fds[i].revents & POLLIN)
			{
				if (_fds[i].fd == server->get_listen_fd())
					server->do_accept();
				else
				{
					server->do_recv(_fds[i]);
					server->print_users();
				}
			}
		}
		_fds.clear();
	}
}

int main(int argc, char *argv[])
{
	signal(SIGINT, handler);
	if (argc != 3)
	{
		std::cerr << "./ircserver <port> <pass>" << std::endl;
		exit(1);
	}
	Server server(argv[1], argv[2]);
	loop(&server);
	server.~Server();
	exit(1);
	// User user("a", "a", 2);
	// std::map<int, User> a;
	// a.insert(std::make_pair(2,user));
	// IMethod *f = new File(a);
	// std::vector<std::string> temp;
	// temp.reserve(4);
	// temp[0] = "file";
	// temp[1] = "SEND";
	// temp[2] = "file";
	// temp[3] = "file";
	// f->execute(temp, 2);
    // Mevcut bağlantı noktası bilgileri
    // int port = 8080;
    // struct sockaddr_in server_address;
    // server_address.sin_family = AF_INET;
    // server_address.sin_addr.s_addr = INADDR_ANY;
    // server_address.sin_port = htons(port);

    // // Yeni soketin bağlantı noktası bilgileri
    // int new_port = 9090;
    // struct sockaddr_in new_address;
    // new_address.sin_family = AF_INET;
    // new_address.sin_addr.s_addr = INADDR_ANY;
    // new_address.sin_port = htons(new_port);

    // // Mevcut soket oluşturma ve bağlantı noktasına bağlanma
    // int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // if (server_fd < 0) {
    //     std::cerr << "Socket creation failed" << std::endl;
    //     return 1;
    // }
    // if (bind(server_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
    //     std::cerr << "Bind failed" << std::endl;
    //     return 1;
    // }
    // if (listen(server_fd, 1) < 0) {
    //     std::cerr << "Listen failed" << std::endl;
    //     return 1;
    // }

    // // Yeni soket oluşturma ve bağlantı noktasına bağlanma
    // int new_fd = socket(AF_INET, SOCK_STREAM, 0);
    // if (new_fd < 0) {
    //     std::cerr << "Socket creation failed" << std::endl;
    //     return 1;
    // }
    // if (bind(new_fd, (struct sockaddr*)&new_address, sizeof(new_address)) < 0) {
    //     std::cerr << "Bind failed" << std::endl;
    //     return 1;
    // }
    // if (listen(new_fd, 1) < 0) {
    //     std::cerr << "Listen failed" << std::endl;
    //     return 1;
    // }
	// char *buffer = new char[1024];
	// int afd = accept(new_fd, NULL, NULL);
	// recv(afd, buffer, sizeof(buffer), 0);
	// if(send(afd, buffer, sizeof(buffer), 0) < 0)
	// {
	// 	perror(std::string("send file " + std::to_string(afd) + " ").c_str());
	// 	return 1;
	// }
    // std::cout << "Sockets created and binded successfully" << " " << buffer<<std::endl;
    // // Sockets'ı kapatma
    // close(server_fd);
    // close(new_fd);

    // return 0;

}
