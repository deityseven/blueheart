#include "signin.h"
#include <httpclient/httpclient.h>
#include <configfile/config_file.h>
#include <message/all>
#include <transmitcenter/transmitcenter.h>
#include <qtimer.h>
#include <qmessagebox.h>

Signin::Signin(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    init();
}

Signin::~Signin()
{
}

void Signin::senderToEmailTimeout()
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

void Signin::signin()
{
    SigninRequest sr;
    sr.setUserName(this->ui.userName->text());
    sr.setPhone(this->ui.phone->text());
    sr.setEmail(this->ui.email->text());
    sr.setCheckNumber(this->ui.checkNumber->text());

    std::string request = TransmitCenter::instance().toJson(&sr);
    std::string response;
    if (!this->httpClient->signin(request, response))
    {
        QMessageBox::warning(this, "错误", QString::fromStdString(response));
        this->sendToEmailTime = 0;
    }
    else
    {
        QMessageBox::information(this, "信息", QString::fromStdString(response));
    }
}

void Signin::senderToEmail()
{
    CheckNumberRequest cnr;
    cnr.setUserName(this->ui.userName->text());
    cnr.setPhone(this->ui.phone->text());
    cnr.setEmail(this->ui.email->text());
    std::string request = TransmitCenter::instance().toJson(&cnr);
    std::string response;
    if (!this->httpClient->getCheckNumber(request, response))
    {
        QMessageBox::warning(this, "错误", QString::fromStdString(response));
        this->sendToEmailTime = 0;
    }
    else
    {
        this->sendToEmailTime = 45;
    }
}

void Signin::init()
{
    ConfigFile cf("./config/network.json");
    cf.beginSection("CheckNumberServer");
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

void Signin::connectSignal()
{
    connect(this->ui.senderToEmail, SIGNAL(clicked()), this, SLOT(senderToEmail()));
    connect(this->ui.signin, SIGNAL(clicked()), this, SLOT(signin()));
    connect(this->sendToEmailTimer, SIGNAL(timeout()), this, SLOT(senderToEmailTimeout()));
}
