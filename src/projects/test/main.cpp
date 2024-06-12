#include <qapplication.h>
#include <executableprogram/executableprogram.h>
#include <json/json.hpp>
#include <qdebug.h>
#include <string>

void RefTest(int argc, char* argv[])
{
	QApplication a(argc, argv);

    ExecutableProgram ep("mysqlclient.exe");

    std::string userName = "admin";
    std::string phone = "18788778749";
    std::string email = "liuguangzhong@163.com";

    ep.addArg("userName","root");
    ep.addArg("password","123456");
    ep.addArg("serverHost","62.234.46.151");
    ep.addArg("setvarPort","3306");
    ep.addArg("database","blueheart");
    ep.addArg("functionNeme","QueryUserNameIsExist");

    nlohmann::json root;
    root["userName"] = userName;
    root["phone"] = phone;
    root["email"] = email;

    std::string temp = root.dump();

    ep.addArg("jsonData", temp);
    std::string result = ep.exec();

    qDebug() << result.c_str();

    a.exec();
}

#include <stdio.h>

int main(int argc, char *argv[])
{
#ifdef I_OS_WIN
    system("chcp 65001");
#endif // WIN
    //{
    //    spdlog::info("user info :");
    //    spdlog::info("{}", client.getCurrentUser()->toJson());
    //}

    printf("main...");
	RefTest(argc, argv);

	return 0;
}