#ifndef DATASRUCTURES_H
#define DATASRUCTURES_H

#include <QDate>
#include <QSet>
#include <QString>
#include <unordered_set>

class Unit {
public:
    Unit() = default;
    ~Unit() = default;
    Unit(const QString& uid) : uid_(uid) {}

    void SetUid(const QString& uid) { uid_ = uid; }
    QString Uid() const { return uid_; }

private:
    // uid
    QString uid_;
};

/* 用户 */
class User : public Unit {
public:
    User() = default;
    ~User() = default;

    QString Name() const;
    void SetName(const QString &new_user_name);

    QString GetProfilePixtureUrl() const;
    void SetProfilePixtureUrl(const QString &new_profile_pixture_url);

    QString Signature() const;
    void SetSignature(const QString &new_signature);

private:
    // 用户昵称
    QString name_;
    // 用户头像
    QString profile_pixture_url_;
    // 用户签名
    QString signature_;

    // 所在群
    std::unordered_set<QString> chat_groups_;
};

/* 聊天记录 */
class ChatHistory : public Unit {
public:

private:
    // 发言者
    QString from_;
    // 时间
    QDate date_;
};

/* 群聊 */
class ChatGroup : public Unit {
public:
    ChatGroup() = default;
    ~ChatGroup() = default;


    QString Name() const;
    void SetName(const QString &new_group_name);

    QString GetProfilePixtureUrl() const;
    void SetProfilePixtureUrl(const QString &new_profile_pixture_url);

    QString Signature() const;
    void SetSignature(const QString &new_signature);

    void AddUsers(std::initializer_list<QString> users);

    std::vector<ChatHistory> ChatHistorys() const;

    QString MasterUid() const;
    void SetMasterUid(const QString &new_master_uid);

private:
    // 群聊昵称
    QString name_;
    // 群聊头像
    QString profile_pixture_url_;
    // 群聊签名
    QString signature_{"..."};

    // 群主uid
    QString master_uid_;
    // 群用户
    std::unordered_set<QString> users_;

    // 聊天记录
    std::vector<ChatHistory> chat_historys_;
};

#endif // DATASRUCTURES_H
