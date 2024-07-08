#ifndef LOGINCHECKNUMBER_H
#define LOGINCHECKNUMBER_H

#include <http/httpserverhandel.h>
#include <util/mysqlserverconfig.h>
#include <util/emailsenderconfig.h>

class LoginCheckNumber : public HttpServerHandle, public MysqlServerConfig, public EmailSenderConfig
{
public:
	LoginCheckNumber(std::string configPath);
	void operator()(const httplib::Request& request, httplib::Response& response) override;
};

#endif // !LOGINCHECKNUMBER_H
