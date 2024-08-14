#include "requestHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>

using namespace std;

string RequestHandler::readFile(const string &filename)
{
    ifstream file(filename, ios::binary);
    if (!file.is_open())
    {
        cerr << "Could not open the file: " << filename << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

string RequestHandler::getContentType(const string &path)
{
    size_t dotPos = path.rfind('.');
    if (dotPos != string::npos)
    {
        string ext = path.substr(dotPos + 1);
        if (ext == "html")
            return "text/html";
        if (ext == "css")
            return "text/css";
        if (ext == "js")
            return "application/javascript";
        if (ext == "eot")
            return "application/vnd.ms-fontobject";
        if (ext == "ttf")
            return "font/ttf";
        if (ext == "woff")
            return "font/woff";
        if (ext == "woff2")
            return "font/woff2";
        if (ext == "svg")
            return "image/svg+xml";
        if (ext == "jpg" || ext == "jpeg")
            return "image/jpeg";
        if (ext == "png")
            return "image/png";
    }
    return "application/octet-stream";
}

void RequestHandler::handleClient(int clientSocket)
{
    char buffer[30000] = {0};
    int bytesRead = 0;
    stringstream requestStream;

    // Read the client's request
    while ((bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytesRead] = '\0';
        requestStream << buffer;
        if (bytesRead < sizeof(buffer) - 1)
            break;
    }

    cout << "Received Request:\n"
         << requestStream.str() << endl;
    
    // Determine the requested file
    string method, path;
    requestStream >> method >> path;

    if (!path.empty() && path[0] == '/')
    {
        path = path.substr(1);
    }

    // Default address
    if (path.empty() || path == "/")
    {
        path = "signin page/index.html";
    }
    else if (path.find("signin%20page/") == string::npos)
    {
        path = "signin page/" + path;
    }

    string fileContent = readFile(path);
    string contentType = getContentType(path);

    string httpResponse;
    if (!fileContent.empty())
    {
        httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: " + contentType + "\r\nContent-Length: " + to_string(fileContent.length()) + "\r\n\r\n" + fileContent;
    }
    else
    {
        httpResponse = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: 0\r\n\r\n";
    }

    write(clientSocket, httpResponse.c_str(), httpResponse.length());
    close(clientSocket);
}
