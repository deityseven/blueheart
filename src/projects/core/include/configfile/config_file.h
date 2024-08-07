#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <string>
#include <list>
#include <map>
#include <typeindex>

class Data
{
public:
    Data(void);
    Data(const char* data);
    Data(std::string data);
    Data(double data);
    Data(int data);
    Data(long data);
    Data(bool data);

    std::string toString() const;
    int toInt() const;
    long toLong() const;
    float toFloat() const;
    double toDouble() const;
    bool toBool() const;

    ~Data() = default;

    template<typename U>
    bool isType() const
    {
        return typeInfo == std::type_index(typeid(U));
    }

private:
    std::string stringData;
    double doubleData;
    long longData;
    bool boolData;

    std::type_index typeInfo;
};

enum class ConfigFileType
{
    None,
    Ini,
    Json,
    Xml
};

//配置文件抽象
class ConfigFile
{
public:
    // 概述：返回配置文件内容的格式
    // 参数：fileContent的值为文件内容
    // 返回值：返回配置文件类型
    static ConfigFileType fileContentFormat(const std::string& fileContent);

public:

    explicit ConfigFile(std::string filePath);
    ~ConfigFile();

    //定位到某个section，默认default
    void beginSection(std::string section = "default");
    //结束section定位
    void endSection();
    //当前section
    std::string section() const;
    //获取key对应的值
    Data value(std::string key) const;
    //设置值
    void setValue(std::string key, Data data);
    //返回当前section下所有 key
    std::list<std::string> allKeys() const;
    //查询当前section下是否存在key，存在返回true
    bool hasKey(std::string key) const;
    //在当前section下删除key以及对应的值，如果key存在并且删除成功返回true
    bool deleteKey(std::string key);
    //同hasKey
    bool contains(std::string key) const;
    //返回当前配置文件是否可以写入
    bool isWritable() const;
    //清空配置内容
    void clear();
    //返回当前配置文件格式
    ConfigFileType type() const;
    //返回当前配置文件路径
    std::string filePath() const;

private:
    //解析文件过程
    void parseFile();
    //输出文件过程
    void outputFile();
    //设置文件格式
    void setFormat(ConfigFileType format);
    //设置文件是否可写
    void setWritable(bool isWritable);

private:
    //       section               key          value
    std::map<std::string, std::map<std::string, Data>> data;
    //配置文件路径
    std::string filePathData;
    //文件格式
    ConfigFileType typeData;
    //是否可写入
    bool isWritableData;
    //配置项已修改
    bool isChange;
    //当前section
    std::string currentSection;
};


#endif // !CONFIG_FILE_H