#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>

class WebServer
{
public:
    WebServer(int port);
    void start();

private:
    int server_fd;
    struct sockaddr_in address;
    int addrlen;

    void handleClient(int clientSocket);
};

#endif
