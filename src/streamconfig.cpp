#include "streamconfig.h"

#include <fstream>
#include <iostream>
#include <sstream>

StreamConfig::StreamConfig() { Init(); }

std::string StreamConfig::ToString() const {
    Json::StreamWriterBuilder writer_builder;
    std::ostringstream os;

    std::unique_ptr<Json::StreamWriter> json_writer(
        writer_builder.newStreamWriter());
    json_writer->write(root_, &os);
    return os.str();
}

bool StreamConfig::FromString(const std::string &str) {
    JSONCPP_STRING errs;
    Json::CharReaderBuilder reader_builder;

    std::unique_ptr<Json::CharReader> const json_reader(
        reader_builder.newCharReader());
    bool res;
    res = json_reader->parse(str.c_str(), str.c_str() + str.length(), &root_,
                             &errs);
    if (!res || !errs.empty()) {
        std::cout << __func__ << " error" << std::endl;
        return false;
    }
    return true;
}

bool StreamConfig::SaveConfig() {
    std::ofstream out(cfg_file_);
    if (out.is_open()) {
        out << ToString();
        out.flush();
        out.close();
        return true;
    } else {
        std::cout << __func__ << " error" << std::endl;
        return false;
    }
}

bool StreamConfig::LoadConfig() {
    std::ifstream in(cfg_file_);
    if (in.is_open()) {
        std::stringstream ss;
        ss << in.rdbuf();
        std::string str(ss.str());
        in.close();
        return FromString(str);
    } else {
        std::cout << __func__ << " error" << std::endl;
        return false;
    }
}

bool StreamConfig::AddStream(size_t project_id, Json::Value stream) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;  // 是否存在对应的project对象
    if (!root.isNull()) {
        for (auto i = 0; i < root.size(); ++i) {
            if (root[i][kId].asUInt() == project_id) {
                exist = true;
                root_[kRoot][i][kStream].append(stream);
                break;
            }
        }
    }
    return exist;
}

bool StreamConfig::AddStream(size_t project_id, size_t id,
                             std::string file_name) {
    Json::Value stream = CreateStream(id, file_name);

    return AddStream(project_id, stream);
}

Json::Value StreamConfig::CreateStream(size_t id, std::string file_name) {
    Json::Value stream;
    stream[kId] = id;
    stream[kType] = kFile;
    stream[kFileNamePath] = file_name;
    return stream;
}

bool StreamConfig::AddStream(size_t project_id, size_t id, std::string port,
                             int baud, int bit, int parity, int stop,
                             int flow) {
    Json::Value stream = CreateStream(id, port, baud, bit, parity, stop, flow);
    return AddStream(project_id, stream);
}

Json::Value StreamConfig::CreateStream(size_t id, std::string port, int baud,
                                       int bit, int parity, int stop,
                                       int flow) {
    Json::Value stream;
    stream[kId] = id;
    stream[kType] = kSerial;
    stream[kPort] = port;
    stream[kBaud] = baud;
    stream[kBit] = bit;
    stream[kParity] = parity;
    stream[kPort] = stop;
    stream[kFlow] = flow;
    return stream;
}

bool StreamConfig::DeleteStream(size_t project_id, size_t id) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;  // 是否存在对应的project对象
    if (!root.isNull()) {
        for (auto i = 0; i < root.size(); ++i) {
            if (root[i][kId].asUInt() == project_id) {
                Json::Value stream = root[i][kStream];
                for (auto j = 0; j < stream.size(); ++j) {
                    if (stream[j][kId].asUInt() == id) {
                        exist = true;
                        root_[kRoot][i][kStream].removeIndex(j, nullptr);
                        break;
                    }
                }
                break;
            }
        }
    }
    return exist;
}

bool StreamConfig::AddProject(std::string project, size_t project_id) {
    Json::Value obj;
    obj[kProject] = project;
    obj[kId] = project_id;
    Json::Value stream;
    root_[kRoot].append(obj);
    return true;
}

bool StreamConfig::DeleteProject(size_t project_id) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;
    if (!root.isNull()) {
        for (auto i = 0; i < root.size(); ++i) {
            if (root[i][kId].asUInt() == project_id) {
                root_[kRoot].removeIndex(i, nullptr);
                exist = true;
                break;
            }
        }
    }
    return exist;
}

bool StreamConfig::EditProject(std::string project, size_t project_id) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;
    if (!root.isNull()) {
        for (auto i = 0; i < root.size(); ++i) {
            if (root[i][kId].asUInt() == project_id) {
                root_[kRoot][i][kProject] = project;
                exist = true;
            }
        }
    }
    return exist;
}

// bool StreamConfig::GetConfig(std::vector<Project_T> &cfg) {
//     Json::Value root;
//     root = root_[kRoot];
//     if (!root.isNull()) {
//         for (auto i = 0; i < root.size(); ++i) {
//             Project_T pro;
//             pro.id = root[i][kId].asUInt();
//             pro.project = root[i][kProject].asString();
//             Json::Value stream = root[i][kStream];
//             if (0 < stream.size()) {
//                 for (auto j = 0; j < stream.size(); ++j) {
//                     Stream_T str;
//                     str.id = stream[j][kId].asUInt();
//                     str.type = stream[j][kType].asString();
//                     StreamRes_T res;
//                     JsonToStreamRes(str.type, stream[j], res);
//                     str.body.push_back(res);
//                     pro.stream.push_back(str);
//                 }
//             }
//             cfg.push_back(pro);
//         }
//     }
//     return true;
// }

bool StreamConfig::GetConfig(std::list<Project_T> &cfg) {
    Json::Value root;
    root = root_[kRoot];
    if (!root.isNull()) {
        for (auto i = 0; i < root.size(); ++i) {
            Project_T pro;
            pro.id = root[i][kId].asUInt();
            pro.project = root[i][kProject].asString();
            Json::Value stream = root[i][kStream];
            if (0 < stream.size()) {
                for (auto j = 0; j < stream.size(); ++j) {
                    Stream_T str;
                    str.id = stream[j][kId].asUInt();
                    str.type = stream[j][kType].asString();
                    StreamRes_T res;
                    JsonToStreamRes(str.type, stream[j], res);
                    str.body.push_back(res);
                    pro.stream.push_back(str);
                }
            }
            cfg.push_back(pro);
        }
    }
    return true;
}

void StreamConfig::Init() { LoadConfig(); }

bool StreamConfig::JsonToStreamRes(const std::string type,
                                   const Json::Value &json,
                                   StreamRes_T &stream) {
    if (type == kFile) {
        // 文件
        auto file = json[kFileNamePath].asString();
        strncpy(stream.file.file, file.c_str(), sizeof(stream.file.file));
    } else if (type == kSerial) {
        // 串口
        auto port = json[kPort].asString();
        strncpy(stream.serial.port, port.c_str(), sizeof(stream.serial.port));
        stream.serial.baud = json[kBaud].asInt();
        stream.serial.bit = json[kBit].asInt();
        stream.serial.parity = json[kParity].asInt();
        stream.serial.stop = json[kStop].asInt();
        stream.serial.flow = json[kFlow].asInt();
    } else {
        // 其他
        return false;
    }
    return true;
}