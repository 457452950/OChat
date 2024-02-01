#include "datasructures.h"


/* 用户 */
QString User::GetProfilePixtureUrl() const
{
    return profile_pixture_url_;
}

void User::SetProfilePixtureUrl(const QString &new_profile_pixture_url)
{
    profile_pixture_url_ = new_profile_pixture_url;
}

QString User::Signature() const
{
    return signature_;
}

void User::SetSignature(const QString &new_signature)
{
    signature_ = new_signature;
}

QString User::Name() const
{
    return name_;
}

void User::SetName(const QString &new_user_name)
{
    name_ = new_user_name;
}


/* 群聊 */
QString ChatGroup::Name() const
{
    return name_;
}

void ChatGroup::SetName(const QString &new_group_name)
{
    name_ = new_group_name;
}

QString ChatGroup::GetProfilePixtureUrl() const
{
    return profile_pixture_url_;
}

void ChatGroup::SetProfilePixtureUrl(const QString &new_profile_pixture_url)
{
    profile_pixture_url_ = new_profile_pixture_url;
}

QString ChatGroup::Signature() const
{
    return signature_;
}

void ChatGroup::SetSignature(const QString &new_signature)
{
    signature_ = new_signature;
}

void ChatGroup::AddUsers(std::initializer_list<QString> users) {
    users_.insert(std::move(users));
}

std::vector<ChatHistory> ChatGroup::ChatHistorys() const
{
    return chat_historys_;
}

QString ChatGroup::MasterUid() const
{
    return master_uid_;
}

void ChatGroup::SetMasterUid(const QString &new_master_uid)
{
    master_uid_ = new_master_uid;
}

void ChatHistory::SetFromTo(const QString &from, const QString &to)
{
    this->from_ = from;
    this->to_ = to;

    if (User::CheckUserUid(to)) {
        this->SetUid(QString("%1_%2_%3").arg(this->from_).arg(this->to_).arg(this->date_));
    } else {
        this->SetUid(QString("%1_%2_%3").arg(this->to_).arg(this->from_).arg(this->date_));
    }
    qDebug() << "chat history uid: " << this->Uid();
}
