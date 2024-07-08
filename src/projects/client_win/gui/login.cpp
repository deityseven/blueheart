#include "login.h"
#include <httpclient/httpclient.h>
#include <configfile/config_file.h>
#include <message/all>
#include <transmitcenter/transmitcenter.h>
#include <qtimer.h>
#include <qmessagebox.h>

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
    if (!this->httpClient->loginCheckNumber(request, response))
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
    
}

void Login::init()
{
    ConfigFile cf("./config/network.json");
    cf.beginSection("SigninServer");
    if (cf.hasKey("host") && cf.hasKey("port"))
    {
        this->httpClient = new HttpClient(cf.value("host").toString(), cf.value("port").toInt());
    }
    else
    {
        this->httpClient = nullptr;
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
