#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "server/includes/server.hpp"
#include <sstream>

#define SERVER_PORT 1234

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[])
{
	if (argc != 3)
		exit(1);
	Server server(argv[1], argv[2]);
	server.loop();
}
