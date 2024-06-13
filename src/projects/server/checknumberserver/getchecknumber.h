#ifndef GETCHECKNUMBER_H
#define GETCHECKNUMBER_H

#include <http/httpserverhandel.h>
#include <util/mysqlserverconfig.h>
#include <util/emailsenderconfig.h>

class GetCheckNumber : public HttpServerHandle, public MysqlServerConfig, public EmailSenderConfig
{
public:
	GetCheckNumber(std::string configPath);
	void operator()(const httplib::Request& request, httplib::Response& response) override;
};

#endif // !GETCHECKNUMBER_H
