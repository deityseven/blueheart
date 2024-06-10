#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <http/httpclientbase.h>

class HttpClient : public HttpClientBase
{
public:
	HttpClient(std::string serverHost, unsigned int serverPort);
	~HttpClient();

	bool getCheckNumber(std::string request, std::string& response);
};


#endif // !HTTPCLIENT_H
