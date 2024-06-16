#include "user.h"

User::User(QString id, QString user_name) : uid(id), name(user_name) {}

MasterUser::MasterUser(QString id, QString user_name) : User(id, user_name) {}
