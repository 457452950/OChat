#ifndef OCHAT__BACKEND_ROOM__CHAT_ENTRY_H
#define OCHAT__BACKEND_ROOM__CHAT_ENTRY_H

#include <QString>
#include <QDateTime>

class ChatMessage {
public:
    enum Type {
        Text,
    };

    QString text;
};

class ChatEntry {
public:
    ChatEntry();

    QString GetUid() const { return uid_; }

    QString From() const { return from_; }

    QString To() const { return to_; }

    int64_t Date() const { return date_; }

    ChatMessage Context() const { return context_; }

private:
    QString uid_;

    QString from_;
    QString to_;

    int64_t date_{QDateTime::currentMSecsSinceEpoch()};

    ChatMessage context_;
};

#endif // OCHAT__BACKEND_ROOM__CHAT_ENTRY_H
