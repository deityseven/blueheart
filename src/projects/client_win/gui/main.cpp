#include <qapplication.h>
#include <qdebug.h>
#include "blueheart.h"
#include <message/all>

void initMessage()
{
    qRegisterMetaType<Message>("Message");
    qRegisterMetaType<CheckNumberRequest>("CheckNumberRequest");
    qRegisterMetaType<Response>("Response");
    qRegisterMetaType<LoginRequest>("LoginRequest");
    qRegisterMetaType<SigninRequest>("SigninRequest");
}
void RefTest(int argc, char* argv[])
{
	QApplication a(argc, argv);

    initMessage();

    BlueHeart bh;
    bh.show();

    a.exec();
}

#include <stdio.h>

int main(int argc, char *argv[])
{
#ifdef I_OS_WIN
    system("chcp 65001");
#endif // WIN

	RefTest(argc, argv);

	return 0;
}