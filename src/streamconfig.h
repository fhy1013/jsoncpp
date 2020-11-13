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
const std::string kType = "type";
const std::string kStreamName = "stream_name";

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
} StreamRes_T;

typedef struct {
    size_t id;                // 流id
    std::string type;         // 流类型
    std::string stream_name;  // 流名称
    StreamRes_T body;         // 流内容
} Stream_T;

typedef struct {
    size_t id;                   // 项目id
    std::string project;         // 项目名称
    std::list<Stream_T> stream;  // 流
} Project_T;

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

    // 添加流，文件类型流
    // param    size_t project_id       I   项目id
    // param    size_t id               I   流id号
    // param    std::string stream_name I   流名称
    // param    std::string file_name   I   文件名 带路径
    // return   true 成功, false 失败
    bool AddStream(size_t project_id, size_t id, std::string stream_name,
                   std::string file_name);

    // 创建流 文件类型流
    // param    size_t id               I   流id号
    // param    std::string stream_name I   流名称
    // param    std::string file_name   I   文件名 带路径
    // return   true 成功, false 失败
    Json::Value CreateStream(size_t id, std::string stream_name,
                             std::string file_name);

    // 添加流 串口类型流
    // param    size_t project_id       I   项目id
    // param    size_t id               I   流id号
    // param    std::string stream_name I   流名称
    // param    std::string port        I   串口号
    // param    std::string baud        I   波特率
    // return   true 成功, false 失败
    bool AddStream(size_t project_id, size_t id, std::string stream_name,
                   std::string port, int baud);

    // 创建流 串口类型流
    // param    size_t id               I   流id号
    // param    std::string stream_name I   流名称
    // param    std::string port        I   串口号
    // param    std::string baud        I   波特率
    // return   true 成功, false 失败
    Json::Value CreateStream(size_t id, std::string stream_name,
                             std::string port, int baud);

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

    // Json 转为 StreamRes 结构体
    // param    const std::string type      I   类型
    // param    const Json::Value &json     I   json对象
    // param    StreamRes &stream           O   StreamRes 结构体
    // return   true 成功, false 失败
    bool JsonToStreamRes(const std::string type, const Json::Value &json,
                         StreamRes_T &stream);

   private:
    Json::Value root_;  // 根节点

    std::string cfg_file_ = ".cfg";  // 配置文件
};

};  // namespace Config

#endif  // STREAMCONFIG_H
