#include "streamconfig.h"

#include <fstream>
#include <iostream>
#include <sstream>

Config::StreamConfig::StreamConfig() { Init(); }

std::string Config::StreamConfig::ToString() const {
    Json::StreamWriterBuilder writer_builder;
    std::ostringstream os;

    std::unique_ptr<Json::StreamWriter> json_writer(
        writer_builder.newStreamWriter());
    json_writer->write(root_, &os);
    return os.str();
}

bool Config::StreamConfig::FromString(const std::string &str) {
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

bool Config::StreamConfig::SaveConfig() {
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

bool Config::StreamConfig::LoadConfig() {
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

bool Config::StreamConfig::AddStream(size_t project_id, Json::Value stream) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;  // 是否存在对应的project对象
    if (!root.isNull()) {
        for (auto i = 0; static_cast<size_t>(i) < root.size(); ++i) {
            if (root[i][kId].asUInt() == project_id) {
                exist = true;
                root_[kRoot][i][kStream].append(stream);
                break;
            }
        }
    }
    return exist;
}

bool Config::StreamConfig::AddStream(const AddStreamCfg_T &cfg) {
    Json::Value stream;
    if (StreamToJson(cfg.stream, stream))
        return AddStream(cfg.id, stream);
    else
        return false;
}

bool Config::StreamConfig::DeleteStream(size_t project_id, size_t id) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;  // 是否存在对应的project对象
    if (!root.isNull()) {
        for (auto i = 0; static_cast<size_t>(i) < root.size(); ++i) {
            if (root[i][kId].asUInt() == project_id) {
                Json::Value stream = root[i][kStream];
                for (auto j = 0; static_cast<size_t>(j) < stream.size(); ++j) {
                    if (stream[j][kId].asUInt() == id) {
                        exist = true;
                        root_[kRoot][i][kStream].removeIndex(
                            static_cast<size_t>(j), nullptr);
                        break;
                    }
                }
                break;
            }
        }
    }
    return exist;
}

bool Config::StreamConfig::AddProject(std::string project, size_t project_id) {
    Json::Value obj;
    obj[kProject] = project;
    obj[kId] = project_id;
    Json::Value stream;
    root_[kRoot].append(obj);
    return true;
}

bool Config::StreamConfig::DeleteProject(size_t project_id) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;
    if (!root.isNull()) {
        for (auto i = 0; static_cast<size_t>(i) < root.size(); ++i) {
            if (root[i][kId].asUInt() == project_id) {
                root_[kRoot].removeIndex(static_cast<size_t>(i), nullptr);
                exist = true;
                break;
            }
        }
    }
    return exist;
}

bool Config::StreamConfig::EditProject(std::string project, size_t project_id) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;
    if (!root.isNull()) {
        for (auto i = 0; static_cast<size_t>(i) < root.size(); ++i) {
            if (root[i][kId].asUInt() == project_id) {
                root_[kRoot][i][kProject] = project;
                exist = true;
            }
        }
    }
    return exist;
}

bool Config::StreamConfig::GetConfig(std::list<Project_T> &cfg) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;
    if (!root.isNull()) {
        for (auto i = 0; static_cast<size_t>(i) < root.size(); ++i) {
            Project_T pro;
            pro.id = root[i][kId].asUInt();
            pro.project = root[i][kProject].asString();
            Json::Value stream = root[i][kStream];
            if (0 < stream.size()) {
                for (auto j = 0; static_cast<size_t>(j) < stream.size(); ++j) {
                    Stream_T res;
                    JsonToStream(stream[j], res);
                    pro.stream.push_back(res);
                    exist = true;
                }
            }
            cfg.push_back(pro);
        }
    }
    return exist;
}

bool Config::StreamConfig::GetConfig(const size_t project_id,
                                     const size_t stream_id, Project_T &cfg) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;
    if (!root.isNull()) {
        for (auto i = 0; static_cast<size_t>(i) < root.size(); ++i) {
            if (root[i][kId].asUInt() == project_id) {
                auto stream = root[i][kStream];
                if (stream.size() > 0) {
                    for (auto j = 0; static_cast<size_t>(j) < stream.size();
                         ++j) {
                        if (stream[j][kId].asUInt() == stream_id) {
                            Stream_T res;
                            JsonToStream(stream[j], res);
                            cfg.stream.push_back(res);
                            cfg.id = project_id;
                            cfg.project = root[i][kProject].asString();
                            exist = true;
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
    return exist;
}

void Config::StreamConfig::Init() { LoadConfig(); }

bool Config::StreamConfig::StreamToJson(const Stream_T &stream_cfg,
                                        Json::Value &stream) {
    bool exist = true;  // 流类型 存在
    if (stream_cfg.head.connect_type == kFile) {
        stream[kFileNamePath] = stream_cfg.body.file.file;
    } else if (stream_cfg.head.connect_type == kSerial) {
        stream[kPort] = stream_cfg.body.serial.port;
        stream[kBaud] = stream_cfg.body.serial.baud;
    } else {
        //
        exist = false;
    }

    if (exist) {
        stream[kId] = stream_cfg.head.id;
        stream[kConnectType] = stream_cfg.head.connect_type;
        stream[kStreamName] = stream_cfg.head.stream_name;
        stream[kStationType] = stream_cfg.head.station_type;
    }
    return exist;
}

bool Config::StreamConfig::JsonToStream(const Json::Value &json,
                                        Stream_T &stream) {
    bool exist = true;
    auto type = json[kConnectType].asString();
    if (type == kFile) {
        // 文件
        strncpy(stream.body.file.file, json[kFileNamePath].asString().c_str(),
                sizeof(stream.body.file.file));
    } else if (type == kSerial) {
        // 串口
        strncpy(stream.body.serial.port, json[kPort].asString().c_str(),
                sizeof(stream.body.serial.port));
        stream.body.serial.baud = json[kBaud].asInt();
    } else {
        exist = false;
    }

    if (exist) {
        stream.head.id = json[kId].asUInt();
        stream.head.connect_type = json[kConnectType].asString();
        stream.head.stream_name = json[kStreamName].asString();
        stream.head.station_type = json[kStationType].asString();
    }
    return exist;
}