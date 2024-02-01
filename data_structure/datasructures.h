#ifndef DATASRUCTURES_H
#define DATASRUCTURES_H

#include <QDate>
#include <QRegularExpression>
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


/**
 * 用户
 *
 * uid : 10000 ~ 99999
 */
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

    static bool CheckUserUid(const QString& uid) { return user_uid_regix.match(uid).hasMatch(); }

private:
    // 用户昵称
    QString name_;
    // 用户头像
    QString profile_pixture_url_;
    // 用户签名
    QString signature_;

    // 所在群
    std::unordered_set<QString> chat_groups_;

    static QRegularExpression user_uid_regix;
};

inline QRegularExpression User::user_uid_regix = QRegularExpression{"^\\d{5}$"};

/**
 * 聊天记录
 *
 * uid: 一对一: {from}_{to}_{date}
 *       群聊: {group}_{from}_{date}
 */
class ChatHistory : public Unit {
public:
    ChatHistory() {}
    ~ChatHistory() {}

    void SetFromTo(const QString& from, const QString& to);

    QString From() { return from_; }

    QDateTime Date() {return QDateTime::fromMSecsSinceEpoch(date_);}

    void SetMessageText(const QString& text) { text_ = text; }
    QString MessageText() { return text_; }

private:
    // 发言者uid
    QString from_;
    // 接受对象uid
    QString to_;
    // 时间
    int64_t date_{QDateTime::currentMSecsSinceEpoch()};
    // context
    QString text_;
};

/**
 * 群聊
 *
 * uid: 1000'0000 ~ 9999'9999
 */
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

    static bool CheckChatGroupUid(const QString& uid) { return chat_group_uid_regix.match(uid).hasMatch(); }

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

    static QRegularExpression chat_group_uid_regix;
};

inline QRegularExpression ChatGroup::chat_group_uid_regix = QRegularExpression{"^\\d{8}$"};

#endif // DATASRUCTURES_H
