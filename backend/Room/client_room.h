#ifndef OCHAT__NACKEND_ROOM__CLIENT_ROOM_H
#define OCHAT__NACKEND_ROOM__CLIENT_ROOM_H

#include "basic.h"
#include "chat_entry.h"

struct ChatRoom {
public:
    ChatRoom();
    ~ChatRoom() = default;

    // 判断群聊
    static bool IsChatGroup(const ChatRoom &chat_room) { return chat_room.masters.size() == 1; }
    bool        IsChatGroup() { return this->masters.size() == 1; }

    QString uid;
    QString name;
    QString signature;
    QString profile_pixture_url;

    std::unordered_set<QString> masters;  // 主持人
    std::unordered_set<QString> managers; // 管理员
    std::unordered_set<QString> members;  // 成员

    std::unordered_map<QString, ChatEntry> chat_history; // 聊天历史
};

#endif // OCHAT__NACKEND_ROOM__CLIENT_ROOM_H
