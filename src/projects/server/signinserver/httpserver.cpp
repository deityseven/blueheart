#include "httpserver.h"
#include <http/httplib.h>
#include "signin.h"

#include <configfile/config_file.h>

HttpServer::HttpServer(std::string serverHost, unsigned int serverPort)
	:HttpServerBase(serverHost, serverPort)
{
}

HttpServer::~HttpServer()
{
}

void HttpServer::serverInit()
{
	Signin signin("./config/network.json");
	this->server->Post("/api/signin", signin);
}
