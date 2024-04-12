#ifndef CHATENTRY_H
#define CHATENTRY_H

#include "Uid.h"

class ChatMessage {
public:
    enum Type { Text };

    QString text;
};

class ChatEntry
{
public:
    ChatEntry();

private:
    Uid id_;

    Uid from_;
    Uid to_;

    int64_t date_{QDateTime::currentMSecsSinceEpoch()};

    ChatMessage context_;
};

#endif // CHATENTRY_H
