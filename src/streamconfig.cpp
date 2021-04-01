#include "streamconfig.h"

JsonConfig::StreamConfig::StreamConfig(std::string cfg_file): JsonConfigAbstract(cfg_file) { }

bool JsonConfig::StreamConfig::AddStream(size_t project_id, Json::Value stream) {
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

bool JsonConfig::StreamConfig::AddStream(const AddStreamCfg_T &cfg) {
    Json::Value stream;
    if (StreamToJson(cfg.stream, stream))
        return AddStream(cfg.id, stream);
    else
        return false;
}

bool JsonConfig::StreamConfig::DeleteStream(size_t project_id, size_t id) {
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

bool JsonConfig::StreamConfig::AddProject(std::string project, size_t project_id, std::string type) {
    Json::Value obj;
    obj[kProject] = project;
    obj[kId] = project_id;
    obj[kProType] = type;

    root_[kRoot].append(obj);
    return true;
}

bool JsonConfig::StreamConfig::DeleteProject(size_t project_id) {
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

bool JsonConfig::StreamConfig::EditProject(std::string project, size_t project_id) {
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

bool JsonConfig::StreamConfig::GetConfig(std::list<Project_T> &cfg) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = true;
    if (!root.isNull()) {
        for (auto i = 0; static_cast<size_t>(i) < root.size(); ++i) {
            Project_T pro;
            pro.id = root[i][kId].asUInt();
            pro.project = root[i][kProject].asString();
            pro.type = root[i][kProType].asString();
            Json::Value stream = root[i][kStream];
            if (0 < stream.size()) {
                for (auto j = 0; static_cast<size_t>(j) < stream.size(); ++j) {
                    Stream_T res;
                    JsonToStream(stream[j], res);
                    pro.stream.push_back(res);
                }
            }
            cfg.push_back(pro);
        }
    }else{
        exist = false;
    }
    return exist;
}

bool JsonConfig::StreamConfig::GetConfig(const size_t project_id,
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
                            cfg.type = root[i][kProType].asString();
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

bool JsonConfig::StreamConfig::StreamToJson(const Stream_T &stream_cfg,
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

bool JsonConfig::StreamConfig::JsonToStream(const Json::Value &json,
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
