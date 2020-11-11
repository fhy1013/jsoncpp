#include <fstream>
#include <iostream>
#include <sstream>

#include "json.h"
#include "streamconfig.h"
#include "test.h"

using namespace std;

// void readStrProJson() {
//     string strValue =
//         "{\"name\":\"shuiyixin\",\"major\":[{\"AI\":\"MachineLearning\"},{"
//         "\"AI\":\"DeepLearning\"},{\"AI\":\"ComputerVision\"}]}";
//     Json::Reader reader;
//     Json::Value value;
//     if (reader.parse(strValue, value)) {
//         string out = value["name"].asString();
//         cout << out << endl;
//         const Json::Value arrayObj = value["major"];
//         for (unsigned int i = 0; i < arrayObj.size(); i++) {
//             out = arrayObj[i]["AI"].asString();
//             cout << out << endl;
//         }
//     }
// }

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
    std::shared_ptr<StreamConfig> stream_cfg_;

    stream_cfg_.reset(new StreamConfig);

    stream_cfg_->AddProject("test", 1);

    // stream_cfg_->AddStream("test1", 1, "./record1.txt");
    // stream_cfg_->AddStream("test2", 2, "./record2.txt");
    // stream_cfg_->AddStream("test1", 3, "./record3.txt");
    // stream_cfg_->AddStream("test3", 4, "COM4", "115200", "5", "0", "1", "0");
    // stream_cfg_->AddStream("test1", 5, "COM5", "38400", "5", "0", "1", "0");
    // stream_cfg_->AddStream("test2", 6, "COM6", "9600", "5", "0", "1", "0");
    // stream_cfg_->AddStream("test1", 7, "COM7", "921600", "5", "0", "1", "0");
    // stream_cfg_->SaveConfig();

    // stream_cfg_->DeleteStream("test1", 1);
    // stream_cfg_->DeleteStream("test3", 4);

    stream_cfg_->SaveConfig();

    int x = 0;

    return;
}

int main() {
    std::cout << "hello..." << std::endl;

    // Test();

    // TestFunc1(2);

    // Test1();

    // JsonFunc();

    TestJson();

    return 0;
}