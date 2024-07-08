#include "checknumberclient.h"

CheckNumberClient::CheckNumberClient(std::string serverHost, unsigned int serverPort)
	:HttpClient(serverHost, serverPort)
{
}

CheckNumberClient::~CheckNumberClient()
{
}

bool CheckNumberClient::siginCheckNumber(std::string request, std::string& response)
{
    return callApi("/api/siginCheckNumber", request, response);
}

bool CheckNumberClient::loginCheckNumber(std::string request, std::string &response)
{
    return callApi("/api/loginCheckNumber", request, response);
}