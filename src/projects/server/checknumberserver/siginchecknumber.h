#ifndef SIGINCHECKNUMBER_H
#define SIGINCHECKNUMBER_H

#include <http/httpserverhandel.h>
#include <util/mysqlserverconfig.h>
#include <util/emailsenderconfig.h>

class SiginCheckNumber : public HttpServerHandle, public MysqlServerConfig, public EmailSenderConfig
{
public:
	SiginCheckNumber(std::string configPath);
	void operator()(const httplib::Request& request, httplib::Response& response) override;
};

#endif // !SIGINCHECKNUMBER_H
