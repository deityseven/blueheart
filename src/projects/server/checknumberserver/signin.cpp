#include "signin.h"
#include <json/json.hpp>
#include <string>
#include <qstring.h>
#include <util/platform_define.h>
#include <executableprogram/executableprogram.h>

Signin::Signin(std::string configPath)
    :MysqlServerConfig(configPath)
{
}

void Signin::operator()(const httplib::Request &request, httplib::Response &response)
{
    auto userInfo = nlohmann::json::parse(request.body);

    std::string userName = userInfo["userName"].get<std::string>();
    std::string phone = userInfo["phone"].get<std::string>();
    std::string email = userInfo["email"].get<std::string>();
    std::string checkNumber = userInfo["checkNumber"].get<std::string>();

#ifdef I_OS_LINUX
        //查询用户是否存在
    ExecutableProgram mysqlclientep("./mysqlclient");
#endif
#ifdef I_OS_WIN
    ExecutableProgram mysqlclientep("mysqlclient.exe");
#endif

    mysqlclientep.addArg("userName",MysqlServerConfig::userName);
    mysqlclientep.addArg("password",MysqlServerConfig::password);
    mysqlclientep.addArg("serverHost",MysqlServerConfig::serverHost);
    mysqlclientep.addArg("serverPort",MysqlServerConfig::serverPort);
    mysqlclientep.addArg("database",MysqlServerConfig::database);
    mysqlclientep.addArg("functionNeme","CheckNumberCompare");

    nlohmann::json userJson;
    userJson["userName"] = userName;
    userJson["phone"] = phone;
    userJson["email"] = email;
    userJson["checkNumber"] = checkNumber;
    std::string temp = userJson.dump();
    printf(temp.c_str());
    QString tt = QString::fromStdString(temp);
    tt.replace("\"","\\\"");
    temp = tt.toStdString();
    mysqlclientep.addArg("jsonData",temp);
    std::string mysqlclientepResult = mysqlclientep.exec();

    auto mysqlclientepResultJson = nlohmann::json::parse(mysqlclientepResult);
    bool success = mysqlclientepResultJson["success"].get<bool>();
    std::string msg = mysqlclientepResultJson["msg"].get<std::string>();
    
    nlohmann::json root;
    root["typeName"] = "SigninResponse";
    root["success"] = success;
    root["msg"] = msg;

    response.body = root.dump();
}
