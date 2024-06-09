#include <configfile/config_file.h>
#include <util/file_util.h>
#include <stdexcept>
#include <climits>
#include <ctype.h>
#include <float.h>
#include "./parser_builder/parser/config_file_content_parser.h"
#include "./parser_builder/builder/config_file_content_builder.h"

Data::Data(void)
    :typeInfo(std::type_index(typeid(void))),
    doubleData(DBL_MAX),
    longData(LONG_MAX),
    boolData(true)
{
}

Data::Data(const char* data)
    :Data(std::string(data))
{
}

Data::Data(std::string data)
    : Data()
{
    this->typeInfo = std::type_index(typeid(std::string));
    this->stringData.swap(data);

    if (data == "true" || data == "false")
    {
        this->boolData = (this->stringData == "true");
        this->typeInfo = std::type_index(typeid(bool));
        return;
    }
    else if (this->stringData.find('.') != std::string::npos)
    {
        auto pos = this->stringData.find('.');
        if (this->stringData.find('.', pos + 1) != std::string::npos)
        {
            return;
        }

        try
        {
            this->doubleData = std::stod(this->stringData);
            this->typeInfo = std::type_index(typeid(double));
            return;
        }
        catch (...)
        {

        }
    }
    else
    {
        bool isdigitFlag = true;
        for (auto& ch : this->stringData)
        {
            if (ch < -1 || ch > 255 || isdigit(ch) == 0 || isxdigit(ch) == 0)
            {
                isdigitFlag = false;
                break;
            }
        }

        if (isdigitFlag == true)
        {
            this->longData = std::stol(this->stringData);
            this->typeInfo = std::type_index(typeid(long));
        }
    }
}

Data::Data(double data)
    : Data()
{
    this->typeInfo = std::type_index(typeid(double));
    this->doubleData = data;
    std::string temp = std::to_string(data);
    this->stringData.swap(temp);
}

Data::Data(int data)
    :Data(long(data))
{
}

Data::Data(long data)
    : Data()
{
    this->typeInfo = std::type_index(typeid(long));
    this->longData = data;
    std::string temp = std::to_string(data);
    this->stringData.swap(temp);
}

Data::Data(bool data)
    : Data()
{
    this->typeInfo = std::type_index(typeid(bool));
    this->boolData = data;
    if (data == true)
    {
        std::string temp("true");
        this->stringData.swap(temp);
    }
    else
    {
        std::string temp("false");
        this->stringData.swap(temp);
    }
}

std::string Data::toString() const
{
    return this->stringData;
}

int Data::toInt() const
{
    return (int)this->longData;
}

float Data::toFloat() const
{
    return (float)this->doubleData;
}

double Data::toDouble() const
{
    return this->doubleData;
}

long Data::toLong() const
{
    return this->longData;
}

bool Data::toBool() const
{
    return this->boolData;
}

ConfigFile::ConfigFile(std::string filePath)
    :currentSection("default"),
    typeData(ConfigFileType::None),
    isWritableData(false),
    isChange(false),
    filePathData(filePath)
{
    parseFile();
}

ConfigFile::~ConfigFile()
{
    if(this->isChange) outputFile();
}

void ConfigFile::beginSection(std::string section)
{
    this->currentSection.swap(section);
}

void ConfigFile::endSection()
{
    this->currentSection = std::string("default");
}

std::string ConfigFile::section() const
{
    return this->currentSection;
}

Data ConfigFile::value(std::string key) const
{
    try
    {
        auto& keyValueMap = this->data.at(currentSection);

        return keyValueMap.at(key);
    }
    catch (...)
    {
        return Data();
    }
}

void ConfigFile::setValue(std::string key, Data data)
{
    try
    {
        auto& keyValueMap = this->data.at(currentSection);

        keyValueMap[key] = data;

        this->isChange = true;
    }
    catch (...)
    {

    }
}

std::list<std::string> ConfigFile::allKeys() const
{
    std::list<std::string> list;

    try
    {
        auto& keyValueMap = this->data.at(currentSection);

        for (auto& pair : keyValueMap)
        {
            list.push_back(pair.first);
        }
    }
    catch (...)
    {
    }

    return list;
}

bool ConfigFile::hasKey(std::string key) const
{
    try
    {
        auto& keyValueMap = this->data.at(currentSection);

        auto iter = keyValueMap.find(key);

        return iter != keyValueMap.end();
    }
    catch (...)
    {
        return false;
    }
}

bool ConfigFile::deleteKey(std::string key)
{
    try
    {
        auto& keyValueMap = this->data.at(currentSection);

        auto iter = keyValueMap.find(key);
        if (iter == keyValueMap.end()) return false;

        keyValueMap.erase(iter);

        this->isChange = true;

        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool ConfigFile::contains(std::string key) const
{
    return hasKey(key);
}

bool ConfigFile::isWritable() const
{
    return this->isWritableData;
}

void ConfigFile::clear()
{
    this->data.clear();
    this->typeData = ConfigFileType::None;
    this->filePathData.clear();

    this->isChange = true;
}

ConfigFileType ConfigFile::type() const
{
    return this->typeData;
}

std::string ConfigFile::filePath() const
{
    return this->filePathData;
}

void ConfigFile::parseFile()
{
    bool isWritable = FileUtil::canWrite(this->filePathData);
    setWritable(isWritable);
    auto fileContent = FileUtil::readAllText(this->filePathData);
    //type
    this->typeData = ConfigFile::fileContentFormat(fileContent);

    ConfigFileContentParser::instance().parseContent(fileContent, this->typeData, this->data);
}

void ConfigFile::outputFile()
{
    if (this->isWritableData == false) return;

    std::string fileContent = ConfigFileContentBuilder::instance().buildFileContent(this->data, this->typeData);

    FileUtil::saveToText(fileContent, this->filePathData);
}

void ConfigFile::setWritable(bool isWritable)
{
    this->isWritableData = isWritable;
}

void ConfigFile::setFormat(ConfigFileType format)
{
    this->typeData = format;
}

ConfigFileType ConfigFile::fileContentFormat(const std::string& fileContent)
{
    bool hasLeftSquareBrackets = (fileContent.find('[') != std::string::npos);
    bool hasRightSquareBrackets = (fileContent.find(']') != std::string::npos);
    bool hasEqualSign = (fileContent.find('=') != std::string::npos);
    bool hasLeftBrace = (fileContent.find('{') != std::string::npos);
    bool hasRightBrace = (fileContent.find('}') != std::string::npos);
    bool hasColon = (fileContent.find(':') != std::string::npos);
    bool hasLeftAngleBrackets = (fileContent.find('<') != std::string::npos);
    bool hasRightAngleBrackets = (fileContent.find('>') != std::string::npos);
    bool hasSlash = (fileContent.find('/') != std::string::npos);

    if (hasSlash && hasLeftAngleBrackets && hasRightAngleBrackets) return ConfigFileType::Xml;
    if (hasLeftBrace && hasRightBrace && hasColon) return ConfigFileType::Json;
    if (hasEqualSign || hasRightSquareBrackets || hasLeftSquareBrackets) return ConfigFileType::Ini;

    return ConfigFileType::None;
}