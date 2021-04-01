#ifndef JSONCONFIG_H
#define JSONCONFIG_H

#include <list>
#include <string>

namespace JsonConfig {

const size_t kFileLen = 1024;
const size_t kSerLen = 256;

const std::string kRoot = "root";
const std::string kProject = "project";
const std::string kProType = "project_type";      // 项目类型
const std::string kProTypeReal = "real_time";     // 实时处理
const std::string kProTypeAfter = "after_wards";  // 事后处理
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

const std::string kTcpServer = "tcp_server";
const std::string kTcpClient = "tcp_client";
const std::string kTcpIP = "tcp_ip";
const std::string kTcpPort = "tcp_port";
// const std::string kBit = "bit";
// const std::string kParity = "parity";
// const std::string kStop = "stop";
// const std::string kFlow = "flow";

const std::string kObjects = "objects";

typedef struct {
    char file[kFileLen];
    int rate;
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
    std::string type;            // 项目类型 real 实时/ after 事后
    std::list<Stream_T> stream;  // 流
} Project_T;

typedef struct {
    size_t id;        // 项目id
    Stream_T stream;  // 流
} AddStreamCfg_T;

}  // namespace JsonConfig

#endif  // JSONCONFIG_H
