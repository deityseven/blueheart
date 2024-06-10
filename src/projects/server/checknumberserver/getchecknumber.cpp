#include "getchecknumber.h"
#include <json/json.hpp>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <array>
#include <util/random_util.hpp>
#include <util/platform_define.h>

void GetCheckNumber::operator()(const httplib::Request& request, httplib::Response& response)
{
#ifdef I_OS_LINUX
    auto userInfo = nlohmann::json::parse(request.body);

    std::string userName = userInfo["userName"].get<std::string>();
    std::string phone = userInfo["phone"].get<std::string>();
    std::string email = userInfo["email"].get<std::string>();

    std::string theme = "blueheart 验证码";
    auto number = RandomUtil::instance().generateInRange(100000, 999999);
    std::string emailContent = "您好，您的验证码是：" + std::to_string(number) + " ,如果不是您进行操作，请忽略此信息。";

    char command[40960] = { 0 };

    sprintf(command,"./emailsender -senderEmail=\"%s\" -senderKey=\"%s\" -recverEmail=\"%s\" -theme=\"%s\" -emailContent=\"%s\" -emailServerHost=\"%s\" -emailServerPort=\"%s\"",
        this->esc.senderEmail.c_str(),
        this->esc.senderKey.c_str(),
        email.c_str(),
        theme.c_str(),
        emailContent.c_str(),
        this->esc.emailServerHost.c_str(),
        this->esc.emailServerPort.c_str());

    std::array<char, 255> buffer;
    std::string result;

    bool isSuccess = false;
    std::string msg;
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        isSuccess = false;
        msg = "验证码发送失败，服务器错误: emailsender popen error";
    }
    else
    {
        int len = fread(buffer.data(), 1, buffer.size(), pipe);

        if (len <= 0) {
            isSuccess = false;
            msg = "验证码发送失败，服务器错误: emailsender print is null";
        }
        else
        {
            if (strcmp(buffer.data(),"error") == 0)
            {
                isSuccess = false;
                msg = "验证码发送失败，服务器错误: emailsender print is error";
            }

            if (strcmp(buffer.data(), "success") == 0)
            {
                isSuccess = true;
                msg = "验证码发送成功";
            }
        }

        pclose(pipe);
    }
    
    nlohmann::json root;
    root["typeName"] = "CheckNumberResponse";
    root["isSuccess"] = true;
    root["msg"] = msg;

    response.body = root.dump();

#endif // I_OS_LINUX
}