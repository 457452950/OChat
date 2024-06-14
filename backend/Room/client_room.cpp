#include "client_room.h"

ChatRoom::ChatRoom() {}

void ChatRoom::SetUid(const QString &id) { this->uid_ = id; }

QString ChatRoom::GetUid() const { return this->uid_; }

void ChatRoom::SetName(const QString &name) { this->name_ = name; }

void ChatRoom::SetSignature(const QString &signature) { this->signature_ = signature; }

void ChatRoom::SetProfilePixtureUrl(const QString &url) { this->profile_pixture_url_ = url; }
