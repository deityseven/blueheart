#include "httpserver.h"
#include <http/httplib.h>
#include "getchecknumber.h"
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
	GetCheckNumber gcn("./config/network.json");
	this->server->Post("/api/getCheckNumber", gcn);
}
