#include "test.h"

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

#include "idmanagement.h"
#include "solveconfig.h"
#include "streamconfig.h"

bool Test() {
    std::string cfg_file = "solve.json";
    JsonConfig::SolveConfig solve(cfg_file);
    size_t project = 1;
    std::multimap<size_t, size_t> obj;
    obj.emplace(1, 2);
    obj.emplace(1, 3);
    obj.emplace(1, 4);
    obj.emplace(2, 1);
    // solve.AddProject(project, obj);
    // solve.SaveConfig();

    size_t project2 = 2;
    // solve.AddProject(project2, obj);
    // solve.SaveConfig();

    std::map<size_t, std::multimap<size_t, size_t>> objects;
    auto res = solve.GetConfig(objects);

    // JsonConfig::SolveConfig solve1(cfg_file);
    // // solve1.DeleteObject(project, obj1);
    // solve1.DeleteProject(project);
    // solve1.SaveConfig();

    // JsonConfig::SolveConfig solve2(cfg_file);
    // // solve2.DeleteProject(project);
    // solve2.AddProject(project, obj);
    // solve2.SaveConfig();

    int x;
    return true;
}

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

void TestJson() { return; }