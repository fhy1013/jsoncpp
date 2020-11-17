#include <fstream>
#include <iostream>
#include <sstream>

#include "json.h"
#include "streamconfig.h"
#include "test.h"

using namespace std;

std::string createJson() {
    std::string jsonStr;
    Json::Value root, lang, mail;
    Json::StreamWriterBuilder writerBuilder;
    std::ostringstream os;

    root["Name"] = "Liming";
    root["Age"] = 26;

    lang[0] = "C++";
    lang[1] = "Java";
    root["Language"] = lang;

    mail["Netease"] = "lmshao@163.com";
    mail["Hotmail"] = "liming.shao@hotmail.com";
    root["E-mail"] = mail;

    std::unique_ptr<Json::StreamWriter> jsonWriter(
        writerBuilder.newStreamWriter());
    jsonWriter->write(root, &os);
    jsonStr = os.str();

    std::cout << "Json:\n" << jsonStr << std::endl;
    return jsonStr;
}

bool parseJson(const std::string &info) {
    if (info.empty()) return false;

    bool res;
    JSONCPP_STRING errs;
    Json::Value root, lang, mail;
    Json::CharReaderBuilder readerBuilder;

    std::unique_ptr<Json::CharReader> const jsonReader(
        readerBuilder.newCharReader());
    res = jsonReader->parse(info.c_str(), info.c_str() + info.length(), &root,
                            &errs);
    if (!res || !errs.empty()) {
        std::cout << "parseJson err. " << errs << std::endl;
    }

    std::cout << "Name: " << root["Name"].asString() << std::endl;
    std::cout << "Age: " << root["Age"].asInt() << std::endl;

    lang = root["Language"];
    std::cout << "Language: ";
    for (int i = 0; i < lang.size(); ++i) {
        std::cout << lang[i] << " ";
    }
    std::cout << std::endl;

    mail = root["E-mail"];
    std::cout << "Netease: " << mail["Netease"].asString() << std::endl;
    std::cout << "Hotmail: " << mail["Hotmail"].asString() << std::endl;

    return true;
}

void JsonFunc() {
    std::string file_name = "./.cfg";
    auto str = createJson();
    std::ofstream out(file_name);
    if (out.is_open()) {
        out << str;
        out.close();
    }

    std::ifstream in(file_name);
    if (in.is_open()) {
        // std::string tmp(std::istreambuf_iterator<char>(in),
        //                 std::istreambuf_iterator<char>());
        std::stringstream ss;
        ss << in.rdbuf();
        std::string tmp(ss.str());
        in.close();
        auto res = parseJson(tmp);
    }
}

void TestJson() {
    std::shared_ptr<Config::StreamConfig> stream_cfg_;

    stream_cfg_.reset(new Config::StreamConfig);

    stream_cfg_->AddProject("pro_1", 1);
    stream_cfg_->AddProject("pro_2", 2);
    stream_cfg_->AddProject("pro_3", 3);
    stream_cfg_->AddProject("pro_4", 4);
    // stream_cfg_->DeleteProject(1);

    Config::AddStreamCfg_T cfg;
    cfg.id = 1;
    Config::Stream_T stream;
    cfg.stream.head.id = 1;
    cfg.stream.head.connect_type = Config::kFile;
    cfg.stream.head.station_type = Config::kBaseStation;
    cfg.stream.head.stream_name = "stream1";
    memcpy(cfg.stream.body.file.file, "./record1", strlen("./record1"));
    stream_cfg_->AddStream(cfg);

    cfg.id = 2;
    cfg.stream.head.id = 2;
    cfg.stream.head.stream_name = "stream2";
    memcpy(cfg.stream.body.file.file, "./record2", strlen("./record2"));
    stream_cfg_->AddStream(cfg);

    cfg.id = 3;
    cfg.stream.head.id = 3;
    cfg.stream.head.stream_name = "stream3";
    memcpy(cfg.stream.body.file.file, "./record3", strlen("./record3"));
    stream_cfg_->AddStream(cfg);

    cfg.stream.head.id = 4;
    cfg.stream.head.stream_name = "stream4";
    cfg.stream.head.connect_type = Config::kSerial;
    cfg.stream.head.station_type = Config::kRoverStation;
    cfg.stream.body.serial.baud = 115200;
    memset(cfg.stream.body.serial.port, 0x00,
           sizeof(cfg.stream.body.serial.port));
    memcpy(cfg.stream.body.serial.port, "COM4", strlen("COM4"));
    stream_cfg_->AddStream(cfg);

    cfg.id = 1;
    cfg.stream.head.id = 5;
    cfg.stream.head.stream_name = "stream5";
    cfg.stream.body.serial.baud = 38400;
    memset(cfg.stream.body.serial.port, 0x00,
           sizeof(cfg.stream.body.serial.port));
    memcpy(cfg.stream.body.serial.port, "COM5", strlen("COM5"));
    stream_cfg_->AddStream(cfg);

    cfg.id = 2;
    cfg.stream.head.id = 6;
    cfg.stream.head.stream_name = "stream6";
    cfg.stream.body.serial.baud = 9600;
    memset(cfg.stream.body.serial.port, 0x00,
           sizeof(cfg.stream.body.serial.port));
    memcpy(cfg.stream.body.serial.port, "COM6", strlen("COM6"));
    stream_cfg_->AddStream(cfg);

    cfg.id = 1;
    cfg.stream.head.id = 7;
    cfg.stream.head.stream_name = "stream7";
    cfg.stream.body.serial.baud = 921600;
    memset(cfg.stream.body.serial.port, 0x00,
           sizeof(cfg.stream.body.serial.port));
    memcpy(cfg.stream.body.serial.port, "COM7", strlen("COM7"));
    stream_cfg_->AddStream(cfg);

    stream_cfg_->SaveConfig();

    // stream_cfg_->DeleteStream(1, 1);
    // stream_cfg_->DeleteStream(2, 2);
    // stream_cfg_->DeleteStream(2, 6);
    // stream_cfg_->EditProject("pro_1_1", 1);

    // stream_cfg_->DeleteProject(3);

    // stream_cfg_->SaveConfig();

    std::list<Config::Project_T> cfg0;
    stream_cfg_->GetConfig(cfg0);

    size_t p_id = 1;
    size_t s_id = 2;
    Config::Project_T cfg1;
    auto res = stream_cfg_->GetConfig(p_id, s_id, cfg1);
    s_id = 5;
    res = stream_cfg_->GetConfig(p_id, s_id, cfg1);

    int x = 0;

    return;
}

int main() {
    std::cout << "hello..." << std::endl;

    Test();

    // TestFunc1(2);

    // Test1();

    // JsonFunc();

    // TestJson();

    return 0;
}