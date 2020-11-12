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

    // stream_cfg_->AddProject("pro_1", 1);
    // stream_cfg_->AddProject("pro_2", 2);
    // stream_cfg_->AddProject("pro_3", 3);
    // stream_cfg_->AddProject("pro_4", 4);
    // // stream_cfg_->DeleteProject(1);

    // stream_cfg_->AddStream(1, 1, "./record1.txt");
    // stream_cfg_->AddStream(2, 2, "./record2.txt");
    // stream_cfg_->AddStream(3, 3, "./record3.txt");
    // stream_cfg_->AddStream(3, 4, "COM4", 115200, 5, 0, 1, 0);
    // stream_cfg_->AddStream(1, 5, "COM5", 38400, 5, 0, 1, 0);
    // stream_cfg_->AddStream(2, 6, "COM6", 9600, 5, 0, 1, 0);
    // stream_cfg_->AddStream(1, 7, "COM7", 921600, 5, 0, 1, 0);
    // stream_cfg_->SaveConfig();

    // stream_cfg_->DeleteStream(1, 1);
    // stream_cfg_->DeleteStream(2, 2);
    // stream_cfg_->DeleteStream(2, 6);
    // stream_cfg_->EditProject("pro_1_1", 1);

    // stream_cfg_->DeleteProject(3);

    // stream_cfg_->SaveConfig();

    std::list<Project_T> cfg;
    stream_cfg_->GetConfig(cfg);

    int x = 0;

    return;
}

// typedef struct {
//     int id;
//     std::string ss;
//     std::list<int> ll;
// } P_T;

// typedef struct {
//     int x;
//     std::string s;
//     std::list<P_T> pt;
// } T_T;

// void GetList(std::list<T_T> &l) {
//     P_T pt;
//     pt.id = 1;
//     pt.ss = "ss";
//     pt.ll.push_back(1);
//     pt.ll.push_back(2);

//     T_T t;
//     t.x = 0;
//     t.s = "s";
//     t.pt.push_back(pt);

//     l.push_back(t);
//     return;
// }

int main() {
    std::cout << "hello..." << std::endl;

    // Test();

    // TestFunc1(2);

    // Test1();

    // JsonFunc();

    TestJson();

    // std::list<T_T> l;
    // GetList(l);

    // int x = 1;

    return 0;
}