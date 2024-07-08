#include "siginclient.h"

SiginClient::SiginClient(std::string serverHost, unsigned int serverPort)
	:HttpClient(serverHost, serverPort)
{
}

SiginClient::~SiginClient()
{
}

bool SiginClient::signin(std::string request, std::string &response)
{
    return callApi("/api/signin", request, response);
}