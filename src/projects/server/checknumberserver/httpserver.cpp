#include "httpserver.h"
#include <http/httplib.h>
#include "siginchecknumber.h"
#include "loginchecknumber.h"
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
	SiginCheckNumber scn("./config/network.json");
	LoginCheckNumber lcn("./config/network.json");
	this->server->Post("/api/siginCheckNumber", scn);
	this->server->Post("/api/loginCheckNumber", lcn);
}
