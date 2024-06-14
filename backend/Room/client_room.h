#ifndef OCHAT__NACKEND_ROOM__CLIENT_ROOM_H
#define OCHAT__NACKEND_ROOM__CLIENT_ROOM_H

#include <unordered_set>
#include <QString>

#include "chat_entry.h"

class ChatRoom {
public:
    ChatRoom();
    ~ChatRoom() = default;

    // 判断群聊
    static bool IsChatGroup(const ChatRoom &chat_room) { return chat_room.masters_.size() == 1; }
    bool        IsChatGroup() { return this->masters_.size() == 1; }

    void    SetUid(const QString &id);
    QString GetUid() const;

    void    SetName(const QString &name);
    QString GetName() const { return name_; }

    void    SetSignature(const QString &signature);
    QString GetSignature() const { return signature_; }

    void    SetProfilePixtureUrl(const QString &url);
    QString GetProfilePixtureUrl() const { return profile_pixture_url_; }

private:
    QString uid_;
    QString name_;
    QString signature_;
    QString profile_pixture_url_;

    std::unordered_set<QString> masters_;  // 主持人
    std::unordered_set<QString> managers_; // 管理员
    std::unordered_set<QString> members_;  // 成员

    std::unordered_map<QString, ChatEntry> chat_history_; // 聊天历史
};

#endif // OCHAT__NACKEND_ROOM__CLIENT_ROOM_H
