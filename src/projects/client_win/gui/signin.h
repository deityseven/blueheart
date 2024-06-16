#pragma once

#include <QWidget>
#include "ui_signin.h"
#include <widget/widgetinit.h>

class HttpClient;
class QTimer;

class Signin : public QWidget, public WidgetInit
{
    Q_OBJECT

public:
    Signin(QWidget *parent = Q_NULLPTR);
    ~Signin();

public slots:
    void senderToEmail();
    void senderToEmailTimeout();
    void signin();
private:
    Ui::Signin ui;

    // 通过 WidgetInit 继承
    virtual void init() override;
    virtual void connectSignal() override;

    HttpClient* checkNumberServerClient;
    HttpClient* signinServerClient;
    QTimer* sendToEmailTimer;
    uint sendToEmailTime;
};
