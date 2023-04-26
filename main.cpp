#include "server/includes/server.hpp"

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
			break;;
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
}
