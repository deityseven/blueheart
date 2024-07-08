#include "login.h"
#include <httpclient/loginclient.h>
#include <httpclient/checknumberclient.h>
#include <configfile/config_file.h>
#include <message/all>
#include <transmitcenter/transmitcenter.h>
#include <qtimer.h>
#include <qmessagebox.h>
#include <executableprogram/ziperprogram.h>

Login::Login(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);

    init();
}

Login::~Login()
{
}

void Login::senderToEmailTimeout()
{
     if (this->sendToEmailTime > 0)
    {
        QString textTemplate = "(%0秒)后再次发送";
        this->ui.senderToEmail->setText(textTemplate.arg(this->sendToEmailTime));
        this->ui.senderToEmail->setEnabled(false);
        --this->sendToEmailTime;
    }
    else
    {
        this->ui.senderToEmail->setText("发送至邮箱");
        this->ui.senderToEmail->setEnabled(true);
        this->sendToEmailTime = 0;
    }
}

void Login::senderToEmail()
{
    CheckNumberRequest cnr;
    cnr.setPhone(this->ui.phone->text());
    cnr.setEmail(this->ui.email->text());
    std::string request = TransmitCenter::instance().toJson(&cnr);
    std::string response;
    if (!this->checkNumberServerClient->loginCheckNumber(request, response))
    {
        QMessageBox::warning(this, "错误", QString::fromStdString(response));
        this->sendToEmailTime = 0;
    }
    else
    {
        this->sendToEmailTime = 45;
    }
}

void Login::login()
{
    LoginRequest lr;
    lr.setPhone(this->ui.phone->text());
    lr.setEmail(this->ui.email->text());
    lr.setCheckNumber(this->ui.checkNumber->text());

    std::string request = TransmitCenter::instance().toJson(&lr);
    std::string userInfo;
    if (!this->loginServerClient->login(request, userInfo))
    {
        QMessageBox::warning(this, "错误", QString::fromStdString(userInfo));
        this->sendToEmailTime = 0;
        return;
    }

    std::string ziperResponse;
    ZiperProgram zp;

    if(zp.zip(".\\users\\blueheart.user", userInfo, ziperResponse))
    {
        QMessageBox::information(this, "信息", "注册成功");
    }
    else
    {
        QMessageBox::warning(this, "错误", QString::fromStdString(ziperResponse));
    }
}

void Login::init()
{
    ConfigFile cf("./config/network.json");
    cf.beginSection("CheckNumberServer");
    if (cf.hasKey("host") && cf.hasKey("port"))
    {
        this->checkNumberServerClient = new CheckNumberClient(cf.value("host").toString(), cf.value("port").toInt());
    }
    else
    {
        this->checkNumberServerClient = nullptr;
    }

    cf.beginSection("LoginServer");
    if (cf.hasKey("host") && cf.hasKey("port"))
    {
        this->loginServerClient = new LoginClient(cf.value("host").toString(), cf.value("port").toInt());
    }
    else
    {
        this->loginServerClient = nullptr;
    }
    
    this->sendToEmailTimer = new QTimer(this);
    this->sendToEmailTime = 0;
    this->sendToEmailTimer->setInterval(1000);
    this->sendToEmailTimer->start();

    connectSignal();
}

void Login::connectSignal()
{
    connect(this->ui.senderToEmail, SIGNAL(clicked()), this, SLOT(senderToEmail()));
    connect(this->ui.login, SIGNAL(clicked()), this, SLOT(login()));
    connect(this->sendToEmailTimer, SIGNAL(timeout()), this, SLOT(senderToEmailTimeout()));
}
