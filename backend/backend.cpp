#include "backend.h"

#include <mutex>

Backend* Backend::instance_ = nullptr;

Backend *Backend::GetInstance() {
    static std::once_flag backend_once_flag;

    std::call_once(backend_once_flag, [&](){
        instance_ = new Backend();
    });

    return instance_;
}

void Backend::Destroy() {
    delete instance_;
    instance_ = nullptr;
}

Backend::Backend() {}

std::shared_ptr<User> Backend::GetUserFromUid(QString uid) {
    auto it = uid_2_users_.find(uid);
    if (it == uid_2_users_.end()) {
        return nullptr;
    }

    return it->second;
}

std::shared_ptr<ChatGroup> Backend::GetGroupFromUid(QString uid) {
    auto it = uid_2_group_.find(uid);
    if (it == uid_2_group_.end()) {
        return nullptr;
    }

    return it->second;
}

void Backend::AddUser(std::shared_ptr<User> user)
{
    this->uid_2_users_.insert({user->Uid(), user});
}

void Backend::AddChatGroup(std::shared_ptr<ChatGroup> group)
{
    this->uid_2_group_.insert({group->Uid(), group});
}
