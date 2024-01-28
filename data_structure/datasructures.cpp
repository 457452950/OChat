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

QString User::UserName() const
{
    return user_name_;
}

void User::SetUserName(const QString &new_user_name)
{
    user_name_ = new_user_name;
}


/* 群聊 */
QString ChatGroup::GroupName() const
{
    return group_name_;
}

void ChatGroup::SetGroupName(const QString &new_group_name)
{
    group_name_ = new_group_name;
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
