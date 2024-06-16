#ifndef OCHAT__NACKEND_ROOM__USER_H
#define OCHAT__NACKEND_ROOM__USER_H


#include "basic.h"

struct User {
public:
    User() = default;
    User(QString id, QString user_name);
    ~User() = default;

    QString uid;
    QString name;
    QString signature;
    QString profile_pixture_url;
};

struct MasterUser : public User {
public:
    MasterUser() = default;
    MasterUser(QString id, QString user_name);
    ~MasterUser() = default;

    UidSet groups;
    UidSet friends;
};

#endif // OCHAT__NACKEND_ROOM__USER_H
