#include "httpclient.h"
#include <http/httplib.h>
#include <json/json.hpp>
#include <transmitcenter/transmitcenter.h>
#include <qvariant.h>

HttpClient::HttpClient(std::string serverHost, unsigned int serverPort)
	:HttpClientBase(serverHost, serverPort)
{
}

HttpClient::~HttpClient()
{
}

bool HttpClient::getCheckNumber(std::string request, std::string& response)
{
    auto result = this->client->Post("/api/getCheckNumber", request, "application/json");

    if (result && (result->status == 200))
    {
        std::string data = result->body;
        QObject* obj = TransmitCenter::instance().fromJson(data);

        bool success = obj->property("success").toBool();
        std::string msg = obj->property("msg").toString().toStdString();

        response = msg;
        return success;
    }

    response = "与服务器通讯失败...请检查网络";
    return false;
}
