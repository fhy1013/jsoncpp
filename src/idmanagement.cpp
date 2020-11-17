#include "idmanagement.h"

size_t ID::IdManagement::GenerateProjectId() {
    size_t id = 0;

    for (size_t i = 1; i < UINT32_MAX; ++i) {
        auto it = project_id_.find(i);
        if (it == project_id_.end()) {
            project_id_.emplace(i);
            id = i;
            break;
        }
    }
    return id;
}

bool ID::IdManagement::DestoryProjectId(size_t id) {
    bool res = false;
    auto it = project_id_.find(id);
    if (it != project_id_.end()) {
        project_id_.erase(it);
        res = true;
    }

    return res;
}

size_t ID::IdManagement::GenerateStreamId() {
    size_t id = 0;
    for (size_t i = 1; i < UINT32_MAX; ++i) {
        auto it = stream_id_.find(i);
        if (it == stream_id_.end()) {
            stream_id_.emplace(i);
            id = i;
            break;
        }
    }
    return id;
}

bool ID::IdManagement::DestoryStreamId(size_t id) {
    bool res = false;
    auto it = stream_id_.find(id);
    if (it != stream_id_.end()) {
        stream_id_.erase(it);
        res = true;
    }

    return res;
}

bool ID::IdManagement::AddProjectId(size_t id) {
    auto it = project_id_.find(id);
    if (it == project_id_.end()) {
        project_id_.emplace(id);
        return true;
    }
    return false;
}

bool ID::IdManagement::AddStreamId(size_t id) {
    auto it = stream_id_.find(id);
    if (it == stream_id_.end()) {
        stream_id_.emplace(id);
        return true;
    }
    return false;
}