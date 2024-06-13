#ifndef MYSQLSERVERCONFIG_H
#define MYSQLSERVERCONFIG_H

#include <string>

class MysqlServerConfig
{
public:
    MysqlServerConfig(std::string path);
    ~MysqlServerConfig();
    std::string userName;
    std::string password;
    std::string serverHost;
    std::string serverPort;
    std::string database;
};

#endif // !MYSQLSERVERCONFIG_H