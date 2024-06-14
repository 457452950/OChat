#ifndef OCHAT__NACKEND_ROOM__USER_H
#define OCHAT__NACKEND_ROOM__USER_H

#include <unordered_set>

#include <QString>
#include <QHash>

class User {
public:
    User() = default;
    User(QString id, QString user_name, const std::unordered_set<QString> &groups = {});
    ~User() = default;

    void    SetUid(const QString &uid) { uid_ = uid; }
    QString GetUid() const { return uid_; }

    void    SetName(const QString &name) { name_ = name; }
    QString GetName() const { return name_; }

    QString GetSignature() const;
    void    SetSignature(const QString &newSignature);

    QString GetProfilePixtureUrl() const;
    void    SetProfilePixtureUrl(const QString &newProfile_pixture_url);

private:
    QString uid_;
    QString name_;
    QString signature_;
    QString profile_pixture_url_;

    std::unordered_set<QString> groups_;
};

#endif // OCHAT__NACKEND_ROOM__USER_H
