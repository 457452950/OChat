#ifndef USER_H
#define USER_H

#include <unordered_set>

#include "Uid.h"

class User
{
public:
    User();
    ~User();


private:
    Uid id_;
    QString user_name_;

    std::unordered_set<Uid, Uid_hash> groups_;
};

#endif // USER_H
