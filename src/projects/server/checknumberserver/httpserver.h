#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <http/httpserverbase.h>

class HttpServer : public HttpServerBase
{
public:
	HttpServer(std::string serverHost, unsigned int serverPort);
	~HttpServer();

	// 通过 HttpServerBase 继承
	virtual void serverInit() override;
};

#endif // !HTTPSERVER_H
