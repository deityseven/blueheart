#include <qapplication.h>

void RefTest(int argc, char* argv[])
{
	QApplication a(argc, argv);

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