#include "blueheart.h"
#include <qfile.h>
#include <qapplication.h>
#include "signin.h"
#include "login.h"

BlueHeart::BlueHeart(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);

    init();
}

BlueHeart::~BlueHeart()
{
}

void BlueHeart::init()
{
    QFile qss(":/blueheart/blueheart.qss");
    if (qss.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(qss.readAll());
    }

    Signin* signin = new Signin;
    this->ui.mainWidget->addWidget(signin);
    Login* login = new Login;
    this->ui.mainWidget->addWidget(login);

    this->ui.mainWidget->setCurrentIndex(1);
    connectSignal();
}

void BlueHeart::connectSignal()
{
}
