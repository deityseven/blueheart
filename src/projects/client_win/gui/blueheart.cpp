#include "blueheart.h"
#include <qfile.h>
#include <qapplication.h>
#include "signin.h"

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

    connectSignal();
}

void BlueHeart::connectSignal()
{
}
