#include "loginclient.h"

LoginClient::LoginClient(std::string serverHost, unsigned int serverPort)
	:HttpClient(serverHost, serverPort)
{
}

LoginClient::~LoginClient()
{
}

bool LoginClient::login(std::string request, std::string &response)
{
    return callApi("/api/login", request, response);
}