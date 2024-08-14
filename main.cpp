#include "server.h"
#include <iostream>

#define PORT 8080

int main()
{
    WebServer server(PORT);
    server.start();
    
    return 0;
}
