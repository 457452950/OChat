#ifndef OCHAT__NACKEND_ROOM__BACKEND_H
#define OCHAT__NACKEND_ROOM__BACKEND_H

#include <lazybox/toy/Instance.hpp>
#include <lazybox/Toy/NonCopyAble.hpp>

#include "Room/client_room.h"
#include "Room/chat_entry.h"
#include "Room/user.h"

class Backend : public lbox::Instance<Backend> {
    friend lbox::Instance<Backend>;

    Backend();

public:
    ~Backend() = default;


    void AddUser(const User &user);
    void AddChatRoom(const ChatRoom &room);

    User     *GetUser(const QString &uid);
    ChatRoom *GetRoom(const QString &uid);

public:
#ifdef QT_DEBUG
    void SetSelf(const User &self) { self_ = self; }
    User self_;
#endif


private:
    std::unordered_map<QString, User>     uid_2_users_;
    std::unordered_map<QString, ChatRoom> uid_2_room_;
};

#endif // OCHAT__NACKEND_ROOM__BACKEND_H
