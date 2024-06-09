#include <http/httpserverbase.h>
#include <http/httplib.h>

HttpServerBase::HttpServerBase(std::string serverHost, unsigned int serverPort)
    :server(nullptr), serverHost(serverHost), serverPort(serverPort)
{
    this->server = new httplib::Server;
}

HttpServerBase::~HttpServerBase()
{
    if (this->server != nullptr) delete this->server;
}

void HttpServerBase::run()
{
    serverInit();

    this->server->listen(serverHost.c_str(), serverPort);
}
