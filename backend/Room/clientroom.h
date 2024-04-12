#ifndef CLIENTROOM_H
#define CLIENTROOM_H

#include <unordered_set>

#include "Uid.h"

class ClientRoom
{
public:
    ClientRoom();
    ~ClientRoom() = default;

private:
    Uid id_;
    QString room_name_;

    std::unordered_set<Uid, Uid_hash> masters_;
    std::unordered_set<Uid, Uid_hash> managers_;
    std::unordered_set<Uid, Uid_hash> members_;

    std::unordered_set<Uid> chat_history_;
};

#endif // CLIENTROOM_H
