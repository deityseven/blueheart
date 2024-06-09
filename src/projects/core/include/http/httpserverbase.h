#ifndef HTTPSERVERBASE_H
#define HTTPSERVERBASE_H

#include <string>

namespace httplib
{
    class Server;
}

class HttpServerBase
{
public:
    HttpServerBase(std::string serverHost, unsigned int serverPort);
    ~HttpServerBase();

    void run();

protected:
    //实现该接口 构建server api
    //类似 this->server->Post("/api/XXX", XXXHandel());
    virtual void serverInit() = 0;

    std::string serverHost;
    unsigned int serverPort;
    httplib::Server* server;
};

#endif // !CONFIG_FILE_H