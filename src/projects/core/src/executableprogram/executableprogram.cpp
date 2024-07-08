#include <executableprogram/executableprogram.h>
#include <string.h>
#include <util/platform_define.h>
#include <array>
#include <json/json.hpp>
#include <stdio.h>
#include <qstring.h>

ExecutableProgram::ExecutableProgram(std::string programPath)
    :path(programPath)
{
}
ExecutableProgram::~ExecutableProgram()
{
}

void ExecutableProgram::addArg(std::string arg, std::string value)
{
    this->args[arg] = value;
}

std::string ExecutableProgram::exec()
{
    nlohmann::json root;
    
    std::string argsStr;
    char buf[4096];
    for(auto item : this->args)
    {
        auto argName = item.first;
        auto argValue = item.second;

        QString temp = QString::fromStdString(argValue);
        argValue = temp.replace("\"", "\\\"").toStdString();

        memset(buf, 0, 4096);
#ifdef I_OS_LINUX
        sprintf(buf," -%s=\"%s\"", argName.c_str(), argValue.c_str());
#endif
#ifdef I_OS_WIN
        sprintf(buf," -%s \"%s\"", argName.c_str(), argValue.c_str());
#endif
        
        argsStr += buf;
    }

    std::string cmd = this->path + argsStr;
    std::array<char, 2550> buffer = { 0 };

#ifdef I_OS_LINUX
    FILE* pipe = popen(cmd.c_str(), "r");
#endif
#ifdef I_OS_WIN
    FILE* pipe = _popen(cmd.c_str(), "r");
#endif

    if (!pipe)
    {
        root["success"] = false;
        root["msg"] = "executable program exec open faile";
    }
    else
    {
        int len = fread(buffer.data(), 1, buffer.size(), pipe);

        if (len <= 0) {
            root["success"] = false;
            root["msg"] = "executable program exec not output";
        }
        else
        {
            root["success"] = true;
            root["msg"] = buffer.data();
        }


#ifdef I_OS_LINUX
        pclose(pipe);
#endif
#ifdef  I_OS_WIN
        _pclose(pipe);
#endif
    }

    std::string result = root.dump();

    return result;
}

bool ExecutableProgram::getExecResult(std::string &msg)
{
    std::string mysqlclientepResult = this->exec();

    auto mysqlclientepResultJson = nlohmann::json::parse(mysqlclientepResult);
    bool success = mysqlclientepResultJson["success"].get<bool>();
    msg = mysqlclientepResultJson["msg"].get<std::string>();

    return success;
}
