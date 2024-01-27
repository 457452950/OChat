#ifndef DATASRUCTURES_H
#define DATASRUCTURES_H

#include <QString>

// 用户
class User {
public:
    User() {}

    QString UserName() const;
    void SetUserName(const QString &new_user_name);

    QString GetProfilePixtureUrl() const;
    void SetProfilePixtureUrl(const QString &new_profile_pixture_url);

    QString Signature() const;
    void SetSignature(const QString &new_signature);

private:
    // 用户uid
    uint32_t uid_{0};
    // 用户昵称
    QString user_name_;
    // 用户头像
    QString profile_pixture_url_;
    // 用户签名
    QString signature_;
};

#endif // DATASRUCTURES_H
