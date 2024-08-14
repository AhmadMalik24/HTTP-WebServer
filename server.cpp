#include "server.h"
#include "requestHandler.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

WebServer::WebServer(int port)
{
    addrlen = sizeof(address);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
}

void WebServer::start()
{
    cout << "\n+++++++ Waiting for new connection ++++++++\n\n";

    while (true)
    {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        thread t(&RequestHandler::handleClient, RequestHandler(), new_socket);
        t.detach();
    }
}
