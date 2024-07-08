#include <executableprogram/ziperprogram.h>

#include <util/platform_define.h>
#include <executableprogram/executableprogram.h>
#include <json/json.hpp>
#include <qbytearray.h>

ZiperProgram::ZiperProgram()
{
#ifdef I_OS_LINUX
    this->ep = new ExecutableProgram("./ziper");
#endif
#ifdef I_OS_WIN
    this->ep = new ExecutableProgram("ziper.exe");
#endif
}

ZiperProgram::~ZiperProgram()
{
    delete this->ep;
}

bool ZiperProgram::zip(std::string filePath, std::string data, std::string& msg)
{
    nlohmann::json jsonData;
    jsonData["filePath"] = filePath;
    QByteArray base64 = QByteArray::fromStdString(data).toBase64();
    jsonData["jsonData"] = base64.toStdString();

    std::string arg = jsonData.dump();
    this->ep->addArg("functionNeme", "Zip");
    this->ep->addArg("jsonData", arg);

    return this->ep->getExecResult(msg);
}
