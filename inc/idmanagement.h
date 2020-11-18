#ifndef ID_MANAGEMENT_H
#define ID_MANAGEMENT_H

#include <map>
#include <set>
namespace ID {

class IdManagement {
   public:
    // 生成项目id
    // 返回值   > 0 id生成成功， 返回id;    == 0 生成失败
    size_t GenerateProjectId();

    // 销毁项目id
    // 返回值   true 成功， false 失败
    bool DestoryProjectId(size_t id);

    // 生成流id
    // 返回值   > 0 id生成成功， 返回id;    == 0 生成失败
    size_t GenerateStreamId();

    // 销毁流id
    // 返回值   true 成功， false 失败
    bool DestoryStreamId(size_t id);

    // 添加项目id
    // 返回值   true 成功， false 失败
    bool AddProjectId(size_t id);

    // 添加流id
    // 返回值   true 成功， false 失败
    bool AddStreamId(size_t id);

   private:
    std::set<size_t> project_id_;
    std::set<size_t> stream_id_;
};  // class IdManagement

}  // namespace ID

#endif  // ID_MANAGEMENT_H