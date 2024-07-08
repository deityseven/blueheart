#ifndef CHECKNUMBERCLIENT_H
#define CHECKNUMBERCLIENT_H

#include <http/httpclient.h>
#include <string>

class CheckNumberClient : public HttpClient
{
public:
	CheckNumberClient(std::string serverHost, unsigned int serverPort);
	~CheckNumberClient();

	bool siginCheckNumber(std::string request, std::string& response);
	bool loginCheckNumber(std::string request, std::string& response);
};


#endif // !CHECKNUMBERCLIENT_H
