#include "solveconfig.h"

JsonConfig::SolveConfig::SolveConfig(std::string cfg_file)
    : JsonConfigAbstract(cfg_file) {}

bool JsonConfig::SolveConfig::AddProject(
    const size_t project, const std::multimap<size_t, size_t> &objects) {
    DeleteProject(project);
    Json::Value obj;
    obj[kProject] = project;
    Json::Value new_objs = ToJson(objects);
    obj[kObjects] = new_objs;
    root_[kRoot].append(obj);
    return true;
}

bool JsonConfig::SolveConfig::DeleteProject(const size_t project) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;
    if (!root.isNull()) {
        for (auto i = 0; static_cast<size_t>(i) < root.size(); ++i) {
            if (root[i][kProject].asUInt() == project) {
                root_[kRoot].removeIndex(static_cast<size_t>(i), nullptr);
                exist = true;
                break;
            }
        }
    }
    return exist;
}

bool JsonConfig::SolveConfig::GetConfig(
    std::map<size_t, std::multimap<size_t, size_t>> &objects) {
    Json::Value root;
    root = root_[kRoot];
    bool exist = false;
    if (!root.isNull()) {
        for (auto i = 0; static_cast<size_t>(i) < root.size(); ++i) {
            auto set_res = FromJson(root[i][kObjects]);
            auto project = root[i][kProject].asUInt();
            if (!set_res.empty()) {
                objects.emplace(project, set_res);
                exist = true;
            }
        }
    }
    return exist;
}

std::multimap<size_t, size_t> JsonConfig::SolveConfig::FromJson(
    const Json::Value &json) {
    std::multimap<size_t, size_t> res;
    for (int i = 0; static_cast<size_t>(i) < json.size(); ++i) {
        std::string val = json[i].asString();
        auto li = Split(val);
        if (li.size() >= 2) {
            res.emplace(
                std::make_pair(atoi(li.at(0).c_str()), atoi(li.at(1).c_str())));
        }
    }
    return res;
}

Json::Value JsonConfig::SolveConfig::ToJson(
    const std::multimap<size_t, size_t> &in) {
    Json::Value res;
    int i = 0;
    for (auto it = in.begin(); it != in.end(); ++i, ++it) {
        std::string val =
            std::to_string(it->first) + ":" + std::to_string(it->second);
        res[i] = val;
    }
    return res;
}

std::vector<std::string> JsonConfig::SolveConfig::Split(
    const std::string &s, const std::string &delim) {
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
    while (pos < len) {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0) {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}