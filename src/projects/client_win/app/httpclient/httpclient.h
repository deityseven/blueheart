#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <http/httpclientbase.h>

class HttpClient : public HttpClientBase
{
public:
	HttpClient(std::string serverHost, unsigned int serverPort);
	~HttpClient();

	bool siginCheckNumber(std::string request, std::string& response);
	bool loginCheckNumber(std::string request, std::string& response);
	bool signin(std::string request, std::string& response);
	bool callApi(std::string api, std::string request, std::string& response);
};


#endif // !HTTPCLIENT_H
