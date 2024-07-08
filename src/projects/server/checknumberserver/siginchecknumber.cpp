#include "siginchecknumber.h"
#include <json/json.hpp>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <array>
#include <util/random_util.hpp>
#include <util/platform_define.h>
#include <executableprogram/executableprogram.h>
#include <executableprogram/mysqlprogram.h>
#include <executableprogram/emailsenderprogram.h>
#include <qstring.h>

SiginCheckNumber::SiginCheckNumber(std::string configPath)
    :EmailSenderConfig(configPath),
    MysqlServerConfig(configPath)
{
}

void SiginCheckNumber::operator()(const httplib::Request &request, httplib::Response &response)
{
    bool success = false;
    std::string msg;

    auto userInfo = nlohmann::json::parse(request.body);

    std::string userName = userInfo["userName"].get<std::string>();
    std::string phone = userInfo["phone"].get<std::string>();
    std::string email = userInfo["email"].get<std::string>();

    std::string theme = "blueheart 验证码";
    auto number = RandomUtil::instance().generateInRange(100000, 999999);
    std::string emailContent = "您好，您的验证码是：" + std::to_string(number) + " ,如果不是您进行操作，请忽略此信息。";

    nlohmann::json userJson;
    userJson["userName"] = userName;
    userJson["phone"] = phone;
    userJson["email"] = email;
    userJson["checkNumber"] = std::to_string(number);
    std::string temp = userJson.dump();
    QString tt = QString::fromStdString(temp);
    tt.replace("\"","\\\"");
    temp = tt.toStdString();
    
    MysqlProgram mp(this);
    if(mp.queryUserNameIsExist(temp, msg))
    {
        success = false;
    }

    if(success)
    {
        EmailSenderProgram esp(this);
        std::string msg;
        if(esp.senderEmail(email, theme, emailContent, msg))
        {
            success = mp.addUserInfo(temp, msg);
        }
        else
        {
            success = false;
            msg = "check number send to email failed";
        }
    }
    
    nlohmann::json root;
    root["typeName"] = "Response";
    root["success"] = success;
    root["msg"] = msg;

    response.body = root.dump();
}