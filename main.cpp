#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>

void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    if (argc != 2) // DO 3 LATER
        error("Usage: ./ircserv <port> <password>\n");

    int sockfd, newsock, valread, portno;
    struct sockaddr_in adress;
    struct pollfd fds;
    int addrlen = sizeof(adress);
    char buffer[1024] = { 0 };
    portno = atoi(argv[1]);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("Socket failed\n");

    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        error("Setsockopt failed\n");

    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr*)&adress, addrlen) < 0)
        error("Bind failed\n");
    if (listen(sockfd, 3) < 0)
        error("Listen failed\n");
    if ((newsock = accept(sockfd, (struct sockaddr*)&adress, (socklen_t*)&addrlen)) < 0)
        error("Accept failed\n");

    // nfds_t num = 1;
    // poll(&fds, num, -1);
    while (1)
    {
        std::string msg;

        bzero(buffer, 1024);
        valread = recv(newsock, buffer, 1024, 0);
        if (valread < 0)
            error ("Error reading\n");
        std::cout << buffer << '\n';

        bzero(buffer, 1024);
        fgets(buffer, 1024, stdin);
        msg = buffer;
        msg += "\r\n";
        valread = send(newsock, msg.c_str(), msg.length(), 0);
        if (valread < 0)
            error ("Error sending\n");
    }
    
    // valread = recv(newsock, buffer, 1024, 0);

    // send(newsock, "Hello from server", strlen("Hello from server"), 0);

    close(newsock);
    shutdown(sockfd, SHUT_RDWR);
    return 0;
}