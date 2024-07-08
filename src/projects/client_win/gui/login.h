#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "ui_login.h"
#include <widget/widgetinit.h>

class CheckNumberClient;
class LoginClient;
class QTimer;

class Login : public QWidget, public WidgetInit
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

public slots:
    void senderToEmail();
    void senderToEmailTimeout();
    void login();
private:
    Ui::Login ui;

    CheckNumberClient* checkNumberServerClient;
    LoginClient* loginServerClient;
    QTimer* sendToEmailTimer;
    uint sendToEmailTime;

    virtual void init() override;
	virtual void connectSignal() override;
};

#endif // LOGIN_H
