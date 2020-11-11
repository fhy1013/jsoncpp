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

bool StreamConfig::AddStream(std::string project, Json::Value stream) {
    Json::Value root;
    root = root_[kRoot];
    bool exit = false;  // 是否存在对应的project对象
    if (!root.isNull()) {
        for (auto i = 0; i < root.size(); ++i) {
            if (root[i][kProject] == project) {
                exit = true;
                root_[kRoot][i][kStream].append(stream);
                break;
            }
        }
    }

    if (!exit) {
        Json::Value obj;
        obj[kProject] = project;
        obj[kStream].append(stream);
        root_[kRoot].append(obj);
    }
    return true;
}

bool StreamConfig::AddStream(std::string project, size_t id,
                             std::string file_name) {
    Json::Value stream = CreateStream(id, file_name);

    return AddStream(project, stream);
}

Json::Value StreamConfig::CreateStream(size_t id, std::string file_name) {
    Json::Value stream;
    stream[kId] = std::to_string(id);
    stream[kType] = kFile;
    stream[kFileNamePath] = file_name;
    return stream;
}

bool StreamConfig::AddStream(std::string project, size_t id, std::string port,
                             std::string baud, std::string bit,
                             std::string parity, std::string stop,
                             std::string flow) {
    Json::Value stream = CreateStream(id, port, baud, bit, parity, stop, flow);
    return AddStream(project, stream);
}

Json::Value StreamConfig::CreateStream(size_t id, std::string port,
                                       std::string baud, std::string bit,
                                       std::string parity, std::string stop,
                                       std::string flow) {
    Json::Value stream;
    stream[kId] = std::to_string(id);
    stream[kType] = kSerial;
    stream[kPort] = port;
    stream[kBaud] = baud;
    stream[kBit] = bit;
    stream[kParity] = parity;
    stream[kPort] = stop;
    stream[kFlow] = flow;
    return stream;
}

bool StreamConfig::DeleteStream(std::string project, size_t id) {
    Json::Value root;
    root = root_[kRoot];
    bool exit = false;  // 是否存在对应的project对象
    if (!root.isNull()) {
        for (auto i = 0; i < root.size(); ++i) {
            if (root[i][kProject] == project) {
                Json::Value stream = root[i][kStream];
                for (auto j = 0; j < stream.size(); ++j) {
                    if (stream[j][kId] == std::to_string(id)) {
                        exit = true;
                        root_[kRoot][i][kStream].removeIndex(j, nullptr);
                        break;
                    }
                }
                if (exit) {
                    Json::Value stream = root_[kRoot][i][kStream];
                    auto size = stream.size();
                    if (0 == stream.size()) {
                        root_[kRoot].removeIndex(i, nullptr);
                    }
                    break;
                }
            }
        }
    }
    return true;
}

bool StreamConfig::AddProject(std::string project, size_t project_id) {
    Json::Value obj;
    obj[kProject] = project;
    obj[kId] = project_id;
    Json::Value stream;
    obj[kStream].append(stream);
    root_[kRoot].append(obj);
}

void StreamConfig::Init() { LoadConfig(); }
