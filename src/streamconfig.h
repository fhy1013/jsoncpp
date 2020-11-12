#ifndef STREAMCONFIG_H
#define STREAMCONFIG_H

#include <list>

#include "json.h"

const size_t kFileLen = 1024;
const size_t kSerLen = 256;

typedef struct {
    char file[kFileLen];
} File_T;
typedef struct {
    char port[kSerLen];
    int baud;
    int bit;
    int parity;
    int stop;
    int flow;
} Serial_T;

typedef union {
    File_T file;
    Serial_T serial;
} StreamRes_T;

typedef struct {
    size_t id;
    std::string type;
    std::list<StreamRes_T> body;
} Stream_T;

typedef struct {
    size_t id;
    std::string project;
    std::list<Stream_T> stream;
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
    // param    std::string file_name   I   文件名 带路径
    // return   true 成功, false 失败
    bool AddStream(size_t project_id, size_t id, std::string file_name);

    // 创建流 文件类型流
    // param    size_t id               I   流id号
    // param    std::string file_name   I   文件名 带路径
    // return   true 成功, false 失败
    Json::Value CreateStream(size_t id, std::string file_name);

    // 添加流 串口类型流
    // param    size_t project_id       I   项目id
    // param    size_t id               I   流id号
    // param    std::string port        I   串口号
    // param    std::string baud        I   波特率
    // param    std::string bit         I   数据位
    // param    std::string parity      I   校验位
    // param    std::string stop        I   停止位
    // param    std::string flow        I   流控
    // return   true 成功, false 失败
    bool AddStream(size_t project_id, size_t id, std::string port, int baud,
                   int bit, int parity, int stop, int flow);

    // 创建流 串口类型流
    // param    size_t id               I   流id号
    // param    std::string port        I   串口号
    // param    std::string baud        I   波特率
    // param    std::string bit         I   数据位
    // param    std::string parity      I   校验位
    // param    std::string stop        I   停止位
    // param    std::string flow        I   流控
    // return   true 成功, false 失败
    Json::Value CreateStream(size_t id, std::string port, int baud, int bit,
                             int parity, int stop, int flow);

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

    // 获取项目配置
    // param    std::list<Project_T> &cfg   I/O     配置结构体链表
    // return   true 成功, false 失败
    // bool GetConfig(std::vector<Project_T> &cfg);
    bool GetConfig(std::list<Project_T> &cfg);

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

    const std::string kRoot = "root";
    const std::string kProject = "project";
    const std::string kStream = "stream";
    const std::string kId = "id";
    const std::string kType = "type";

    const std::string kFile = "file";
    const std::string kFileNamePath = "file_name_path";

    const std::string kSerial = "serial";
    const std::string kPort = "port";
    const std::string kBaud = "baud";
    const std::string kBit = "bit";
    const std::string kParity = "parity";
    const std::string kStop = "stop";
    const std::string kFlow = "flow";
};

#endif  // STREAMCONFIG_H
