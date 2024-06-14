#ifndef SIGNIN_H
#define SIGNIN_H

#include <http/httpserverhandel.h>
#include <util/mysqlserverconfig.h>

class Signin : public HttpServerHandle, public MysqlServerConfig
{
public:
	Signin(std::string configPath);
	void operator()(const httplib::Request& request, httplib::Response& response) override;
};

#endif // !SIGNIN_H
