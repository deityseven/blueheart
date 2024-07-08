#include "msyqlprogram.h"
#include <util/platform_define.h>
#include <executableprogram/executableprogram.h>
#include <util/mysqlserverconfig.h>
#include <json/json.hpp>

MysqlProgram::MysqlProgram(MysqlServerConfig* msc)
{
#ifdef I_OS_LINUX
    this->ep = new ExecutableProgram("./mysqlclient");
#endif
#ifdef I_OS_WIN
    this->ep = new ExecutableProgram("mysqlclient.exe");
#endif

    this->ep->addArg("userName",msc->userName);
    this->ep->addArg("password",msc->password);
    this->ep->addArg("serverHost",msc->serverHost);
    this->ep->addArg("serverPort",msc->serverPort);
    this->ep->addArg("database",msc->database);
}

MysqlProgram::~MysqlProgram()
{
    delete this->ep;
}

bool MysqlProgram::queryUserNameIsExist(std::string jsonData, std::string &msg)
{
    this->ep->addArg("functionNeme","QueryUserNameIsExist");
    this->ep->addArg("jsonData", jsonData);

    std::string result;
    bool success = parseResult(result);

    if(success)
    {
        auto queryUserNameIsExistResultJson = nlohmann::json::parse(result);
        bool success0 = queryUserNameIsExistResultJson["success"].get<bool>();
        msg = queryUserNameIsExistResultJson["msg"].get<std::string>();

        return success0;
    }

    msg = result;
    return false;
}

bool MysqlProgram::addUserInfo(std::string jsonData, std::string &msg)
{
    this->ep->addArg("functionNeme","AddUserInfo");
    this->ep->addArg("jsonData", jsonData);

    std::string result;
    bool success = parseResult(result);

    if(success)
    {
        auto addUserInfoResultJson = nlohmann::json::parse(result);
        bool success0 = addUserInfoResultJson["success"].get<bool>();
        msg = addUserInfoResultJson["msg"].get<std::string>();

        return success0;
    }

    msg = result;
    return false;
}

bool MysqlProgram::parseResult(std::string &msg)
{
    std::string mysqlclientepResult = this->ep->exec();

    auto mysqlclientepResultJson = nlohmann::json::parse(mysqlclientepResult);
    bool success = mysqlclientepResultJson["success"].get<bool>();
    msg = mysqlclientepResultJson["msg"].get<std::string>();

    return success;
}
