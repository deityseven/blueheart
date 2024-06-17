#include "getchecknumber.h"
#include <json/json.hpp>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <array>
#include <util/random_util.hpp>
#include <util/platform_define.h>
#include <executableprogram/executableprogram.h>
#include <qstring.h>

GetCheckNumber::GetCheckNumber(std::string configPath)
    :EmailSenderConfig(configPath),
    MysqlServerConfig(configPath)
{
}

void GetCheckNumber::operator()(const httplib::Request &request, httplib::Response &response)
{
    auto userInfo = nlohmann::json::parse(request.body);

    std::string userName = userInfo["userName"].get<std::string>();
    std::string phone = userInfo["phone"].get<std::string>();
    std::string email = userInfo["email"].get<std::string>();

    std::string theme = "blueheart 验证码";
    auto number = RandomUtil::instance().generateInRange(100000, 999999);
    std::string emailContent = "您好，您的验证码是：" + std::to_string(number) + " ,如果不是您进行操作，请忽略此信息。";
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
    mysqlclientep.addArg("functionNeme","QueryUserNameIsExist");

    nlohmann::json userJson;
    userJson["userName"] = userName;
    userJson["phone"] = phone;
    userJson["email"] = email;
    userJson["checkNumber"] = std::to_string(number);
    std::string temp = userJson.dump();
    QString tt = QString::fromStdString(temp);
    tt.replace("\"","\\\"");
    temp = tt.toStdString();
    mysqlclientep.addArg("jsonData",temp);
    std::string mysqlclientepResult = mysqlclientep.exec();
    printf(mysqlclientepResult.c_str());

    auto mysqlclientepResultJson = nlohmann::json::parse(mysqlclientepResult);
    bool success = mysqlclientepResultJson["success"].get<bool>();
    std::string msg = mysqlclientepResultJson["msg"].get<std::string>();
    if(success)
    {
        
#ifdef I_OS_LINUX
        ExecutableProgram emailsenderep("./emailsender");
#endif
#ifdef I_OS_WIN
        ExecutableProgram emailsenderep("emailsender.exe");
#endif
        emailsenderep.addArg("senderEmail",EmailSenderConfig::senderEmail);
        emailsenderep.addArg("senderKey",EmailSenderConfig::senderKey);
        emailsenderep.addArg("recverEmail",email);
        emailsenderep.addArg("emailServerHost",EmailSenderConfig::emailServerHost);
        emailsenderep.addArg("emailServerPort",EmailSenderConfig::emailServerPort);
        emailsenderep.addArg("theme",theme);
        emailsenderep.addArg("emailContent",emailContent);
    
        std::string emailsenderepResult = emailsenderep.exec();
        auto jsonObject = nlohmann::json::parse(emailsenderepResult);
        bool success = jsonObject["success"].get<bool>();
        std::string msg = jsonObject["msg"].get<std::string>();

        if(success)
        {
            mysqlclientep.addArg("functionNeme","AddUserInfo");

            std::string mysqlclientepResult = mysqlclientep.exec();
            printf(mysqlclientepResult.c_str());
            auto mysqlclientepResultJson = nlohmann::json::parse(mysqlclientepResult);
            bool success = mysqlclientepResultJson["success"].get<bool>();
            std::string msg = mysqlclientepResultJson["msg"].get<std::string>();

            nlohmann::json root;
            root["typeName"] = "CheckNumberResponse";
            root["success"] = success;
            root["msg"] = msg;

            response.body = root.dump();

            return;
        }
        else
        {
            bool success = false;
            std::string msg = "check number send to email failed";

            nlohmann::json root;
            root["typeName"] = "CheckNumberResponse";
            root["success"] = success;
            root["msg"] = msg;

            response.body = root.dump();

            return;
        }
    }
    
    nlohmann::json root;
    root["typeName"] = "CheckNumberResponse";
    root["success"] = success;
    root["msg"] = msg;

    response.body = root.dump();
}