#include "signin.h"
#include <json/json.hpp>
#include <string>
#include <qstring.h>
#include <util/platform_define.h>
#include <executableprogram/mysqlprogram.h>
#include <util/random_util.hpp>

Signin::Signin(std::string configPath)
    :MysqlServerConfig(configPath)
{
}

void Signin::operator()(const httplib::Request &request, httplib::Response &response)
{
    bool success;
    std::string msg;

    auto userInfo = nlohmann::json::parse(request.body);

    std::string userName = userInfo["userName"].get<std::string>();
    std::string phone = userInfo["phone"].get<std::string>();
    std::string email = userInfo["email"].get<std::string>();
    std::string checkNumber = userInfo["checkNumber"].get<std::string>();

    nlohmann::json userJson;
    userJson["userName"] = userName;
    userJson["phone"] = phone;
    userJson["email"] = email;
    userJson["checkNumber"] = checkNumber;
    std::string temp = userJson.dump();
    QString tt = QString::fromStdString(temp);
    tt.replace("\"","\\\"");
    temp = tt.toStdString();

    MysqlProgram mp(this);
    if(success = mp.checkNumberCompare(temp, msg))
    {
        //生成用户密码保存到数据库后发送给客户端
        auto password = RandomUtil::instance().generateInRange(100000000, 999999999);
        userJson["password"] = std::to_string(password);

        std::string temp = userJson.dump();
        QString tt = QString::fromStdString(temp);
        tt.replace("\"","\\\"");
        temp = tt.toStdString();
        if(success = mp.updateUserPassword(temp, msg))
        {
            msg = userJson.dump();
        }
    }

    nlohmann::json root;
    root["typeName"] = "Response";
    root["success"] = success;
    root["msg"] = msg;

    response.body = root.dump();
}
