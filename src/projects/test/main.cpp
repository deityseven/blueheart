#include <qapplication.h>

#include <transmitcenter/transmitcenter.h>
#include <transmitcenter/serializable.h>
#include "client_win/app/message/checknumber.h"
#include "client_win/app/message/signinrequest.h"
#include <qdebug.h>

void RefTest(int argc, char* argv[])
{
	QApplication a(argc, argv);

    qRegisterMetaType<Serializable>("Serializable");
    qRegisterMetaType<Message>("Message");
    qRegisterMetaType<CheckNumber>("CheckNumber");
    qRegisterMetaType<SigninRequest>("SigninRequest");

    CheckNumber cn;
    cn.setPhone("123");
    cn.setEmail("456");
    cn.setUserName("XXX");

    auto json = TransmitCenter::instance().toJson(&cn);

    SigninRequest sr;
    sr.setPhone("123");
    sr.setEmail("456");
    sr.setUserName("XXX");
    sr.setCheckNumber("999");

    auto json1 = TransmitCenter::instance().toJson(&sr);
    auto object2 = TransmitCenter::instance().fromJson(json1);
    auto json2 = TransmitCenter::instance().toJson(object2);
    qDebug() << json2.c_str();

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