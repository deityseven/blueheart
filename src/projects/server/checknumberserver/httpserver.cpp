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
	ConfigFile cf("./config/network.json");
	cf.beginSection("EmailSender");
	GetCheckNumber gcn;
	gcn.esc.emailServerHost = cf.value("emailServerHost").toString();
	gcn.esc.emailServerPort = cf.value("emailServerPort").toString();
	gcn.esc.senderEmail = cf.value("senderEmail").toString();
	gcn.esc.senderKey = cf.value("senderKey").toString();
	cf.endSection();

	this->server->Post("/api/getCheckNumber", gcn);
}
