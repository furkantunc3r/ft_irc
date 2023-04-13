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

// int main()
// {
// 	int len, rc, on = 1;
// 	int listen_sd = -1, new_sd = -1;
// 	int desc_ready, end_server = FALSE, compress_array = FALSE;
// 	int close_conn;
// 	char buffer[80];
// 	struct sockaddr_in addr;
// 	int timeout;
// 	struct pollfd fds[200];
// 	int nfds = 1, current_size = 0, i, j;

// 	memset((char *)&addr, 0, sizeof(addr));
// 	addr.sin_family = AF_INET;
// 	addr.sin_addr.s_addr = INADDR_ANY;
// 	addr.sin_port = htons(SERVER_PORT);
// 	listen_sd = socket(AF_INET, SOCK_STREAM, 0);
// 	setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
// 	bind(listen_sd, (struct sockaddr *)&addr, (socklen_t)sizeof(addr));
// 	listen(listen_sd, 1024);

// 	fds[0].fd = listen_sd;
// 	fds[0].events = POLLIN;
// 	fds[0].revents = 0;

// 	while (1)
// 	{
// 		poll(fds, nfds, -1);
// 		for (size_t i = 0; i < nfds; i++)
// 		{
// 			if (fds[i].revents & POLLIN)
// 			{
// 				if (fds[i].fd == listen_sd)
// 				{
// 					sockaddr_in s_address = {};
// 					socklen_t s_size = sizeof(s_address);
// 					new_sd = accept(listen_sd, NULL, NULL);
// 					fds[nfds].fd = new_sd;
// 					fds[nfds].events = POLLIN;
// 					fds[nfds].revents = 0;
// 					nfds++;
// 				}
// 				rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
// 				if (rc < 0)
// 				{
// 					if (errno != EWOULDBLOCK)
// 					{
// 						perror("  recv() failed");
// 						close_conn = TRUE;
// 					}
// 					break;
// 				}
// 				if (rc == 0)
// 				{
// 					printf("  Connection closed\n");
// 					close_conn = TRUE;
// 					break;
// 				}
// 				len = rc;
// 				printf("  %d bytes received\n", len);
// 				std::cout << buffer << std::endl;
// 				rc = send(fds[i].fd, buffer, len, 0);
// 				if (rc < 0)
// 				{
// 					perror("  send() failed");
// 					close_conn = TRUE;
// 					break;
// 				}
// 			}
// 		}
// 	}
// }

int main(int argc, char *argv[])
{
	// int len, rc, on = 1;
	// int listen_sd = -1, new_sd = -1;
	// int desc_ready, end_server = FALSE, compress_array = FALSE;
	// int close_conn;
	// unsigned char buffer[80];
	// struct sockaddr_in addr;
	// int timeout;
	// struct pollfd fds[200];
	// int nfds = 1, current_size = 0, i, j;

	// listen_sd = socket(AF_INET, SOCK_STREAM, 0);

	// rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR,
	// 				(char *)&on, sizeof(on));

	// rc = fcntl(listen_sd, F_SETFL, O_NONBLOCK);

	// memset(&addr, 0, sizeof(addr));
	// addr.sin_family = AF_INET;
	// // memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	// addr.sin_port = htons(SERVER_PORT);
	// rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));
	// rc = listen(listen_sd, 32);
	// memset(fds, 0, sizeof(fds));

	// fds[0].fd = listen_sd;
	// fds[0].events = POLLIN;

	// do
	// {
	// 	printf("Waiting on poll()... %d\n", nfds);
	// 	rc = poll(fds, nfds, -1);
	// 	if (rc < 0)
	// 	{
	// 		perror("  poll() failed");
	// 		break;
	// 	}
	// 	if (rc == 0)
	// 	{
	// 		printf("  poll() timed out.  End program.\n");
	// 		break;
	// 	}
	// 	current_size = nfds;
	// 	for (i = 0; i < current_size; i++)
	// 	{
	// 		if (fds[i].revents & POLLIN)
	// 		{
	// 			if (fds[i].fd == listen_sd)
	// 			{
	// 				printf("  Listening socket is readable\n");
	// 				do
	// 				{
	// 					new_sd = accept(listen_sd, NULL, NULL);
	// 					if (new_sd < 0)
	// 					{
	// 						if (errno != EWOULDBLOCK)
	// 						{
	// 							perror("  accept() failed");
	// 							end_server = TRUE;
	// 						}
	// 						break;
	// 					}
	// 					printf("  New incoming connection - %d\n", new_sd);
	// 					fds[nfds].fd = new_sd;
	// 					fds[nfds].events = POLLIN;
	// 					nfds++;
	// 				} while (new_sd != -1);
	// 			}
	// 			else
	// 			{
	// 				printf("  Descriptor %d is readable\n", fds[i].fd);
	// 				close_conn = FALSE;
	// 				rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
	// 				if (rc < 0)
	// 					break;
	// 				if (rc == 0)
	// 				{
	// 					printf("  Connection closed\n");
	// 					close_conn = TRUE;
	// 					break;
	// 				}
	// 				len = rc;
	// 				printf("  %d bytes received %s\n", len, buffer);
	// 				if (std::string((char *)buffer).find("QUIT") != std::string::npos)
	// 				{
	// 					nfds--;
	// 					fds[i].fd  = -1;
	// 					break;
	// 				}
	// 				rc = send(fds[i].fd, buffer, len, 0);
	// 			} /* End of existing connection is readable             */
	// 		}
	// 		if (close_conn)
	// 		{
	// 			close(fds[i].fd);
	// 			fds[i].fd = -1;
	// 			compress_array = TRUE;
	// 		}
	// 	} /* End of loop through pollable descriptors              */
	// 	if (compress_array)
	// 	{
	// 		compress_array = FALSE;
	// 		for (i = 0; i < nfds; i++)
	// 		{
	// 			std::cout << fds[i].fd << std::endl;
	// 			if (fds[i].fd == -1)
	// 			{
	// 				for (j = i; j < nfds; j++)
	// 				{
	// 					fds[j].fd = fds[j + 1].fd;
	// 				}
	// 				i--;
	// 				nfds--;
	// 			}
	// 		}
	// 	}

	// } while (end_server == FALSE); /* End of serving running.    */

	// /*************************************************************/
	// /* Clean up all of the sockets that are open                 */
	// /*************************************************************/
	// for (i = 0; i < nfds; i++)
	// {
	// 	if (fds[i].fd >= 0)
	// 		close(fds[i].fd);
	// }
	if (argc != 2)
		exit(1);
	Server server(argv[1]);
	server.loop();
}
