#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>

int main()
{
    int sockfd, newsock, valread;
    struct sockaddr_in adress;
    struct pollfd fds;
    int addrlen = sizeof(adress);
    char buffer[1024] = { 0 };

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(1234);
    if (bind(sockfd, (struct sockaddr*)&adress, addrlen) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    if ((newsock = accept(sockfd, (struct sockaddr*)&adress, (socklen_t*)&addrlen)) < 0)
    {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    nfds_t num = 1;
    poll(&fds, num, -1);
    valread = recv(newsock, buffer, 1024, 0);
    std::cout << buffer << '\n';
    send(newsock, "Hello from server", strlen("Hello from server"), 0);
    std::cout << "Message sent!\n";

    close(newsock);
    shutdown(sockfd, SHUT_RDWR);
    return 0;
}