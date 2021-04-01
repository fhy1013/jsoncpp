#ifndef STREAMCONFIG_H
#define STREAMCONFIG_H

#include "jsonconfigabstract.h"

namespace JsonConfig {

class StreamConfig : public JsonConfigAbstract{
   public:
    enum CfgType { NONE, SERIAL, FILE };

   public:
    StreamConfig(std::string cfg_file = "stream.json");

    // 添加流
    // param    size_t project_id       I   项目id
    // param    Json::Value             I   json流对象
    // return   true 成功, false 失败
    bool AddStream(size_t project_id, Json::Value stream);

    // 添加流
    // param    const AddStreamCfg_T &cfg   I   流配置
    // return   true 成功, false 失败
    bool AddStream(const AddStreamCfg_T &cfg);

    //  删除流
    //  size_t project_id               I   项目id
    // param    size_t id               I   流id号
    // return   true 成功, false 失败
    bool DeleteStream(size_t project_id, size_t id);

    // 添加项目
    // param    std::string project     I   项目名称
    // param    size_t project_id       I   项目id
    // param    std::string type        I   项目类型
    // return   true 成功, false 失败
    bool AddProject(std::string project, size_t project_id, std::string type);

    // 删除项目
    //  size_t project_id   I   项目id
    // return   true 成功, false 失败
    bool DeleteProject(size_t project_id);

    // 编辑项目
    // param    std::string project     I   项目名称
    // param    size_t project_id       I   项目id
    // return   true 成功, false 失败
    bool EditProject(std::string project, size_t project_id);

    // 获取所有项目配置
    // param    std::list<Project_T> &cfg   I/O     配置结构体链表
    // return   true 获取成功, false 获取失败
    bool GetConfig(std::list<Project_T> &cfg);

    // 获取单个流配置
    // param    const size_t project_id     I   项目id
    // param    const size_t stream_id      I   流id
    // param    Project_T &cfg              O   配置结构体
    // return   true 获取成功, false 获取失败
    bool GetConfig(const size_t project_id, const size_t stream_id,
                   Project_T &cfg);

   private:
    // Stream_T 转 Json
    // param    const Stream_T &stream  I   流配置
    // param    Json::Value &stream     O   Json 对象
    // return   true 成功, false 失败
    bool StreamToJson(const Stream_T &stream_cfg, Json::Value &stream);

    // Json 转 Stream_T
    // param    const Json::Value &json I   Json流对象
    // param    Stream_T &stream        O   Stream_T 对象
    // return   true 成功, false 失败
    bool JsonToStream(const Json::Value &json, Stream_T &stream);

};

}  // namespace JsonConfig

#endif  // STREAMCONFIG_H
