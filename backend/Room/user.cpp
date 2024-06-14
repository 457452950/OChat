#include "user.h"

User::User(QString id, QString user_name, const std::unordered_set<QString> &groups) :
    uid_(id), name_(user_name), groups_(groups) {}

QString User::GetSignature() const { return signature_; }

void User::SetSignature(const QString &newSignature) { signature_ = newSignature; }

QString User::GetProfilePixtureUrl() const { return profile_pixture_url_; }

void User::SetProfilePixtureUrl(const QString &newProfile_pixture_url) {
    profile_pixture_url_ = newProfile_pixture_url;
}
