#ifndef BLUEHEART_H
#define BLUEHEART_H

#include <QWidget>
#include "ui_blueheart.h"

class BlueHeart : public QWidget
{
    Q_OBJECT

public:
    explicit BlueHeart(QWidget *parent = nullptr);
    ~BlueHeart();

private:
    Ui::BlueHeart ui;
};

#endif // BLUEHEART_H
