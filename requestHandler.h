#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <string>

class RequestHandler
{
public:
    void handleClient(int clientSocket);

private:
    std::string readFile(const std::string &filename);
    std::string getContentType(const std::string &path);
};

#endif
