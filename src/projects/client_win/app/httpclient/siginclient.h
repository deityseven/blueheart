#ifndef SIGINCLIENT_H
#define SIGINCLIENT_H

#include <http/httpclient.h>
#include <string>

class SiginClient : public HttpClient
{
public:
	SiginClient(std::string serverHost, unsigned int serverPort);
	~SiginClient();

	bool signin(std::string request, std::string& response);
};


#endif // !SIGINCLIENT_H
