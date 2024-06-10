#ifndef BLUEHEART_H
#define BLUEHEART_H

#include <QWidget>
#include "ui_blueheart.h"
#include <widget/widgetinit.h>

class BlueHeart : public QWidget, public WidgetInit
{
    Q_OBJECT

public:
    explicit BlueHeart(QWidget *parent = nullptr);
    ~BlueHeart();

private:
    Ui::BlueHeart ui;

    // 通过 WidgetInit 继承
    virtual void init() override;
    virtual void connectSignal() override;
};

#endif // BLUEHEART_H
