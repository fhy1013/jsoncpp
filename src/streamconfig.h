#ifndef STREAMCONFIG_H
#define STREAMCONFIG_H

#include <list>

#include "json.h"

namespace Config {

const size_t kFileLen = 1024;
const size_t kSerLen = 256;

const std::string kRoot = "root";
const std::string kProject = "project";
const std::string kStream = "stream";
const std::string kId = "id";
const std::string kConnectType = "connect_type";
const std::string kStreamName = "stream_name";
const std::string kStationType = "station_type";
const std::string kBaseStation = "base_station";
const std::string kRoverStation = "rover_station";

const std::string kFile = "file";
const std::string kFileNamePath = "file_name_path";

const std::string kSerial = "serial";
const std::string kPort = "port";
const std::string kBaud = "baud";
// const std::string kBit = "bit";
// const std::string kParity = "parity";
// const std::string kStop = "stop";
// const std::string kFlow = "flow";

typedef struct {
    char file[kFileLen];
} File_T;
typedef struct {
    char port[kSerLen];
    int baud;
    //    int bit;
    //    int parity;
    //    int stop;
    //    int flow;
} Serial_T;

typedef union {
    File_T file;
    Serial_T serial;
} StreamBody_T;

typedef struct {
    size_t id;                 // 流id
    std::string connect_type;  // 流连接类型
    std::string stream_name;   // 流名称
    std::string station_type;  // 站点类型
} StreamHead_T;

typedef struct {
    StreamHead_T head;  // 流 内容头
    StreamBody_T body;  // 流 内容体
} Stream_T;

typedef struct {
    size_t id;                   // 项目id
    std::string project;         // 项目名称
    std::list<Stream_T> stream;  // 流
} Project_T;

typedef struct {
    size_t id;        // 项目id
    Stream_T stream;  // 流
} AddStreamCfg_T;

class StreamConfig {
   public:
    enum CfgType { NONE, SERIAL, FILE };

   public:
    StreamConfig();

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
    // return   true 成功, false 失败
    bool AddProject(std::string project, size_t project_id);

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
    void Init();

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

   private:
    Json::Value root_;  // 根节点

    std::string cfg_file_ = ".cfg";  // 配置文件
};

};  // namespace Config

#endif  // STREAMCONFIG_H
