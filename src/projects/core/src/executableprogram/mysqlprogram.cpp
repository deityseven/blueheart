#include <executableprogram/mysqlprogram.h>
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
    bool success = this->ep->getExecResult(msg);

    if(success)
    {
        auto resultJson = nlohmann::json::parse(result);
        bool success0 = resultJson["success"].get<bool>();
        msg = resultJson["msg"].get<std::string>();

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
    bool success = this->ep->getExecResult(msg);

    if(success)
    {
        auto resultJson = nlohmann::json::parse(result);
        bool success0 = resultJson["success"].get<bool>();
        msg = resultJson["msg"].get<std::string>();

        return success0;
    }

    msg = result;
    return false;
}

bool MysqlProgram::checkNumberCompare(std::string jsonData, std::string &msg)
{
    this->ep->addArg("functionNeme","CheckNumberCompare");
    this->ep->addArg("jsonData", jsonData);

    std::string result;
    bool success = this->ep->getExecResult(msg);

    if(success)
    {
        auto resultJson = nlohmann::json::parse(result);
        bool success0 = resultJson["success"].get<bool>();
        msg = resultJson["msg"].get<std::string>();

        return success0;
    }

    msg = result;
    return false;
}
bool MysqlProgram::updateUserPassword(std::string jsonData, std::string &msg)
{
    this->ep->addArg("functionNeme","UpdateUserPassword");
    this->ep->addArg("jsonData", jsonData);

    std::string result;
    bool success = this->ep->getExecResult(msg);

    if(success)
    {
        auto resultJson = nlohmann::json::parse(result);
        bool success0 = resultJson["success"].get<bool>();
        msg = resultJson["msg"].get<std::string>();

        return success0;
    }

    msg = result;
    return false;
    return false;
}