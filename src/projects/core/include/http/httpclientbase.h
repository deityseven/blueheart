#ifndef HTTPCLIENTBASE_H
#define HTTPCLIENTBASE_H

#include <string>

namespace httplib
{
    class Client;
}

class HttpClientBase
{
public:
    HttpClientBase(std::string serverHost, unsigned int serverPort);
    ~HttpClientBase();

    //api存在
    bool apiCheck(std::string api);
    //读超时
    void setReadTimeout(unsigned int millisecond);
    //写超时
    void setWriteTimeout(unsigned int millisecond);

protected:
    httplib::Client* client;
};

#endif // !CONFIG_FILE_H