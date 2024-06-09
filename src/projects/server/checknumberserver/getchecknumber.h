#ifndef GETCHECKNUMBER_H
#define GETCHECKNUMBER_H

#include <http/httpserverhandel.h>

class GetCheckNumber : public HttpServerHandle
{
public:

	struct EmailServerConfig
	{
        std::string senderEmail;
        std::string senderKey;
        std::string emailServerHost;
        std::string emailServerPort;
	};

	EmailServerConfig esc;

	void operator()(const httplib::Request& request, httplib::Response& response) override;
};

#endif // !GETCHECKNUMBER_H
