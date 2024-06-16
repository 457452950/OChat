#ifndef OCHAT__BACKEND_ROOM__CHAT_ENTRY_H
#define OCHAT__BACKEND_ROOM__CHAT_ENTRY_H

#include <QString>
#include <QDateTime>

struct ChatMessage {
    enum Type {
        Text,
    };

    QString text;
};

struct ChatEntry {
public:
    ChatEntry();

    QString uid;

    QString from;
    QString to;

    int64_t date{QDateTime::currentMSecsSinceEpoch()};

    ChatMessage context;
};

#endif // OCHAT__BACKEND_ROOM__CHAT_ENTRY_H
