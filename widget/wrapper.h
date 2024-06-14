#ifndef OCHAT__WIDGET__WRAPPER_H
#define OCHAT__WIDGET__WRAPPER_H

#include <tuple>
#include <unordered_map>
#include <unordered_set>

#include "backend/backend.h"


class ObjectChangeList {
public:
    void UserUpdate(const User &new_user) { this->user_change_list_[new_user.GetUid()] = new_user; }

    class Listener {
    public:
        virtual void OnUserUpdate(const User &user) {}
        virtual void OnChatRoomUpdate(const ChatRoom &room) {}
    };

    void Register(Listener *listener, std::unordered_set<QString> uids) {
        this->listeners_[listener] = std::move(uids);
    }
    void UnRegister(Listener *listener) { this->listeners_.erase(listener); }

    void Update() {
        for(auto [lis, uids] : listeners_) {
            for(auto [uid, user] : user_change_list_) {
                if(uids.count(uid) > 0) {
                    lis->OnUserUpdate(user);
                }
            }
        }
    }

private:
    std::unordered_map<QString, User>                           user_change_list_;
    std::unordered_map<Listener *, std::unordered_set<QString>> listeners_;
};


#endif // OCHAT__WIDGET__WRAPPER_H
