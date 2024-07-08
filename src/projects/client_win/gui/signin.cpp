#include "signin.h"
#include <httpclient/siginclient.h>
#include <httpclient/checknumberclient.h>
#include <configfile/config_file.h>
#include <message/all>
#include <transmitcenter/transmitcenter.h>
#include <qtimer.h>
#include <qmessagebox.h>
#include <executableprogram/executableprogram.h>
#include <json/json.hpp>

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
    if (!this->signinServerClient->signin(request, response))
    {
        QMessageBox::warning(this, "错误", QString::fromStdString(response));
        this->sendToEmailTime = 0;
    }
    else
    {
        ExecutableProgram ziper("ziper.exe");

        nlohmann::json jsonData;
        jsonData["filePath"] = ".\\users\\blueheart.user";
        QByteArray base64 = QByteArray::fromStdString(response).toBase64();
        jsonData["jsonData"] = base64.toStdString();

        std::string arg = jsonData.dump();
        ziper.addArg("functionNeme", "Zip");
        ziper.addArg("jsonData", arg);

        std::string ziperResponse = ziper.exec();
        printf(ziperResponse.c_str());

        auto ziperResponseJson = nlohmann::json::parse(ziperResponse);

        bool success = ziperResponseJson["success"].get<bool>();
        std::string msg = ziperResponseJson["msg"].get<std::string>();

        if (success)
        {
            QMessageBox::information(this, "信息", "注册成功");
        }
        else
        {
            QMessageBox::warning(this, "错误", QString::fromStdString(msg));
        }
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
    if (!this->checkNumberServerClient->siginCheckNumber(request, response))
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
        this->checkNumberServerClient = new CheckNumberClient(cf.value("host").toString(), cf.value("port").toInt());
    }
    else
    {
        this->checkNumberServerClient = nullptr;
    }

    cf.beginSection("SigninServer");
    if (cf.hasKey("host") && cf.hasKey("port"))
    {
        this->signinServerClient = new SiginClient(cf.value("host").toString(), cf.value("port").toInt());
    }
    else
    {
        this->signinServerClient = nullptr;
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
