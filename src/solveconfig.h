#ifndef SOLVECONFIG_H
#define SOLVECONFIG_H

#include <set>

#include "jsonconfigabstract.h"

namespace JsonConfig {

class SolveConfig : public JsonConfigAbstract {
   public:
    SolveConfig(std::string cfg_file = "solve.json");

    // 添加项目
    // param const size_t project                           I   项目id
    // param const std::multimap<size_t, size_t> &objects   I   解算对 id集合
    // return   true 成功, false 失败
    bool AddProject(const size_t project,
                    const std::multimap<size_t, size_t> &objects);

    // 删除项目
    // param const size_t project   I   项目id
    // return   true 成功, false 失败
    bool DeleteProject(const size_t project);

    // 获取配置
    // param std::map<size_t, std::multimap<size_t, size_t>> &objects  O
    // 对象集合<项目id，解算对 id集合>
    // return   true 成功, false 失败
    bool GetConfig(std::map<size_t, std::multimap<size_t, size_t>> &objects);

   private:
    // Json对象转为 集合
    // param const Json::Value &json    I   Json 对象
    // 返回值 multimap集合
    std::multimap<size_t, size_t> FromJson(const Json::Value &json);

    // 集合转为 Json对象
    // param const std::multimap<size_t, size_t> &in    I set集合
    // 返回值 json对象
    Json::Value ToJson(const std::multimap<size_t, size_t> &in);

    // string 字符串分割
    // param const std::string &s           I   字符串
    // param const std::string &delim = ":" I   分割字符串，默认":""
    std::vector<std::string> Split(const std::string &s,
                                   const std::string &delim = ":");
};

}  // namespace JsonConfig

#endif  // SOLVECONFIG_H
