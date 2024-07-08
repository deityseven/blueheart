#ifndef LOGINCLIENT_H
#define LOGINCLIENT_H

#include <http/httpclient.h>
#include <string>

class LoginClient : public HttpClient
{
public:
	LoginClient(std::string serverHost, unsigned int serverPort);
	~LoginClient();

	bool login(std::string request, std::string& response);
};


#endif // !LOGINCLIENT_H
