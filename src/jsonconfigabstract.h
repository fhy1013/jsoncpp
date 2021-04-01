#ifndef JSONCONFIGABSTRACT_H
#define JSONCONFIGABSTRACT_H

#include "jsonconfig.h"
#include "json.h"

namespace JsonConfig{

class JsonConfigAbstract
{
public:
    JsonConfigAbstract(std::string cfg_file = ".json");

    // json 转为string
    std::string ToString() const;

    // 从string转为json 对象
    // param    const std::string &str  I   输入字符串
    // return   true 成功, false 失败
    bool FromString(const std::string &str);

    // 保存流配置到文件
    // return   true 成功, false 失败
    bool SaveConfig();

    // 加载配置文件中的配置
    // return   true 成功, false 失败
    bool LoadConfig();

private:
    void Init();

protected:
    Json::Value root_;  // 根节点

    std::string cfg_file_;  // 配置文件
};

} // namespace JsonConfig

#endif // JSONCONFIGABSTRACT_H
