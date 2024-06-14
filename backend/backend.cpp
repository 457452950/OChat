#include "backend.h"


Backend::Backend() {}

void Backend::AddUser(const User &user) { this->uid_2_users_.insert({user.GetUid(), user}); }

void Backend::AddChatRoom(const ChatRoom &room) { this->uid_2_room_[room.GetUid()] = room; }

User *Backend::GetUser(const QString &uid) {
    auto it = this->uid_2_users_.find(uid);
    if(it != this->uid_2_users_.end()) {
        return &it->second;
    }
    return nullptr;
}

ChatRoom *Backend::GetRoom(const QString &uid) {
    auto it = this->uid_2_room_.find(uid);
    if(it != this->uid_2_room_.end()) {
        return &it->second;
    }
    return nullptr;
}
