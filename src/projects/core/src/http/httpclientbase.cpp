#include <http/httpclientbase.h>
#include <http/httplib.h>
#include <json/json.hpp>

HttpClientBase::HttpClientBase(std::string serverHost, unsigned int serverPort)
{
	this->client = new httplib::Client(serverHost, serverPort);
}

HttpClientBase::~HttpClientBase()
{
	if (this->client != nullptr) delete this->client;
}

bool HttpClientBase::apiCheck(std::string api)
{
	auto result = this->client->Post(api.c_str());

    if (result && (result->status == 200))
        return true;

    return false;
}

void HttpClientBase::setReadTimeout(unsigned int millisecond)
{
	this->client->set_read_timeout(0, millisecond);
}

void HttpClientBase::setWriteTimeout(unsigned int millisecond)
{
	this->client->set_write_timeout(0, millisecond);
}
