#ifndef OCHAT__WIDGET__WRAPPER_H
#define OCHAT__WIDGET__WRAPPER_H

#include <tuple>
#include <map>
#include <set>
#include <unordered_set>

#include "backend/Room/basic.h"

enum ObjectChangeType {
    Add,
    Del,
    Mod,
};

struct ChangeEvent {
    QString          uid;
    ObjectChangeType type;

    bool operator<(const ChangeEvent &event) const { return this->uid < event.uid; }
};

class EventWrapperManager {
public:
    void Update(const QString &uid, ObjectChangeType type) {
        if(this->uid_to_observers_.count(uid) > 0)
            this->change_event_list_.insert({uid, type});
    }

    class Listener {
    public:
        virtual void OnObjectUpdate(const ChangeEvent &event) = 0;
    };

    template <class Container>
    void Register(Listener *listener, Container &&container) {
        listeners_[listener].clear();

        for(const QString &uid : container) {
            uid_to_observers_[uid].insert(listener);
            auto itt = uid_to_observers_.find(uid);
            listeners_[listener].push_back(itt);
        }
    }
    void Register(Listener *listener, std::initializer_list<QString> &&container) {
        listeners_[listener].clear();

        for(const QString &uid : container) {
            uid_to_observers_[uid].insert(listener);
            auto itt = uid_to_observers_.find(uid);
            listeners_[listener].push_back(itt);
        }
    }
    void UnRegister(Listener *listener) {
        for(auto it : listeners_[listener]) {
            uid_to_observers_.erase(it);
        }
        listeners_[listener].clear();
    }

    void Flush() {
        for(auto &event : change_event_list_) {
            if(uid_to_observers_.count(event.uid)) {
                for(auto listener : uid_to_observers_[event.uid]) {
                    listener->OnObjectUpdate(event);
                }
            }
        }
    }

private:
    std::set<ChangeEvent> change_event_list_;

    // std::map 防止 iterator 失效
    using UidToObserverMap = std::map<QString, std::unordered_set<Listener *>>;

    UidToObserverMap                                              uid_to_observers_;
    std::map<Listener *, std::vector<UidToObserverMap::iterator>> listeners_;
};


#endif // OCHAT__WIDGET__WRAPPER_H
