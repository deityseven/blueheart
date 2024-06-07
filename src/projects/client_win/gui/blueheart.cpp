#include "blueheart.h"
#include <qfile.h>
#include <qapplication.h>

BlueHeart::BlueHeart(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);

    QFile qss(":/blueheart/blueheart.qss");
    if(qss.open(QIODevice::ReadOnly))
    {
        this->setStyleSheet(qss.readAll());
    }
}

BlueHeart::~BlueHeart()
{
}
