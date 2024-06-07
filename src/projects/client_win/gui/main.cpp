#include <qapplication.h>
#include <qdebug.h>
#include "blueheart.h"

void RefTest(int argc, char* argv[])
{
	QApplication a(argc, argv);

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