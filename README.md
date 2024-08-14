# HTTP Web Server in C++
This is a simple multithreaded HTTP web server built using C++ and sockets. The server can serve static files such as HTML, CSS, JavaScript, images, and fonts. 
It handles multiple connections via threads, allowing multiple clients to connect simultaneously.
___

## Features

+ Serve static files 'HTML' 'CSS' 'JS' 'Images' 'Fonts'
+ Multithreaded handling of client connections
+ Simple content-type detection based on file extensions

## Prerequisites
- C++11 or later
- Linux-based environment (for arpa/inet.h, netinet/in.h, sys/socket.h headers)

## How to Compile
**To compile the project, you can use the following command in the project directory:**
```g++ main.cpp server.cpp requestHandler.cpp -o webServer```

## How to Run
**After compiling, you can run the server using the command:**
```./webServer```

## Directory Structure
├── README.md
├── main.cpp              # Main server code
├── fileHandler.cpp       # Handles file reading logic
├── fileHandler.h         # Header for file handling
├── clientHandler.cpp     # Handles individual client connections
├── clientHandler.h       # Header for client handling
├── signin page/          # Directory with HTML files (example static files)
│   └── index.html        # Default page

## How It Works
**Server Initialization:** *The server is initialized and starts listening on the specified port* (**default** is '8080').
**Client Handling:** When a client connects, a new thread is created to handle the request. The server reads the request, determines the requested file, and serves it to the client.
**File Serving:** *The server reads the requested file* (**e.g.**, 'HTML', 'CSS', 'JavaScript', 'images') *from the signin page/ directory and sends it back to the client with the appropriate content type.*
**Multithreading:** *The server can handle multiple client connections simultaneously, thanks to multithreading.*
