#include <executableprogram/executableprogram.h>
#include <string.h>
#include <message/checknumberresponse.h>
#include <transmitcenter/transmitcenter.h>

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
    CheckNumberResponse cnr;

    std::string argsStr;
    char buf[4096];
    for(auto item : this->args)
    {
        auto argName = item.first;
        auto argValue = item.second;
        memset(buf, 0, 4096);
        sprintf(buf," -%s=\"%s\"",argName.c_str(),argValue.c_str());
        argsStr += buf;
    }

    std::string cmd = this->path + argsStr;
    std::array<char, 2550> buffer;

#ifdef I_OS_LINUX
    FILE* pipe = popen(cmd.c_str(), "r");
#endif
#ifdef I_OS_WIN
    FILE* pipe = _popen(cmd.c_str(), "r");
#endif

    if (!pipe)
    {
        cnr.setSuccess(false);
        cnr.setMsg("executable program exec open faile");
    }
    else
    {
        int len = fread(buffer.data(), 1, buffer.size(), pipe);

        if (len <= 0) {
            cnr.setSuccess(false);
            cnr.setMsg("executable program exec not output");
        }
        else
        {
            cnr.setSuccess(true);
            cnr.setMsg(buffer.data());
        }


#ifdef I_OS_LINUX
        pclose(pipe);
#endif
#ifdef  I_OS_WIN
        _pclose(pipe);
#endif
    }

    std::string result = TransmitCenter::instance().toJson(&cnr);

    return result;
}
