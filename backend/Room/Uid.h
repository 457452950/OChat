#ifndef UID_H
#define UID_H

#include <QString>

#include "../../common/config/clientsetting.h"

class Uid : protected QString {
public:
    enum Type {
        Unknown = -1, User = 0, Chat = 1, Room = 2, ChatHistory = 3
    } ;

    Type GetType() const;
    QString GetUid() const;

    bool SetUserId(const QString& user_id);
    bool SetRoomId(const QString& room_id);
    bool SetChatEntryId(const QString& chat_entry_id);

    // oprator
    using QString::operator==;
    using QString::operator!=;

    // find
    using QString::indexOf;
    using QString::lastIndexOf;
    using QString::startsWith;
    using QString::endsWith;
    using QString::contains;
    using QString::count;

    // split
    using QString::split;
    using QString::at;
    using QString::mid;
    using QString::left;
    using QString::right;


private:
    Type type{Unknown};

    void SetUid(const QString& uid);
};

inline Uid::Type Uid::GetType() const
{
    return type;
}

inline QString Uid::GetUid() const
{
    return *this;
}

inline bool Uid::SetUserId(const QString &user_id)
{
    if (SETTING->UserUidRegStr.match(user_id).hasMatch()) {
        this->type = User;
        this->SetUid(user_id);
        return true;
    }
    return false;
}

inline bool Uid::SetRoomId(const QString &room_id)
{
    if (SETTING->ChatUidRegStr.match(room_id).hasMatch()) {
        this->type = Chat;
        this->SetUid(room_id);
        return true;
    }
    else if (SETTING->RoomUidRegStr.match(room_id).hasMatch()) {
        this->type = Room;
        this->SetUid(room_id);
        return true;
    }
    return false;
}

inline bool Uid::SetChatEntryId(const QString &chat_entry_id)
{
    if (SETTING->ChatEntryUidRegStr.match(chat_entry_id).hasMatch()) {
        this->type = ChatHistory;
        this->SetUid(chat_entry_id);
        return true;
    }
    return false;
}

inline void Uid::SetUid(const QString & uid)
{
    this->clear();
    this->append(uid);
}


struct Uid_hash
{
    size_t operator()(const Uid& uid) const
    {
        return std::hash<QString>()(uid.GetUid());
    }
};

#endif // UID_H
