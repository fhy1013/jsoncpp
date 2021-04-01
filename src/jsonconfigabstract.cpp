#include "jsonconfigabstract.h"

#include <iostream>
#include <fstream>

JsonConfig::JsonConfigAbstract::JsonConfigAbstract(std::string cfg_file):cfg_file_(cfg_file)
{
    Init();
}

std::string JsonConfig::JsonConfigAbstract::ToString() const {
    Json::StreamWriterBuilder writer_builder;
    std::ostringstream os;

    std::unique_ptr<Json::StreamWriter> json_writer(
        writer_builder.newStreamWriter());
    json_writer->write(root_, &os);
    return os.str();
}

bool JsonConfig::JsonConfigAbstract::FromString(const std::string &str) {
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

bool JsonConfig::JsonConfigAbstract::SaveConfig() {
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

bool JsonConfig::JsonConfigAbstract::LoadConfig() {
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

void JsonConfig::JsonConfigAbstract::Init() { LoadConfig(); }
