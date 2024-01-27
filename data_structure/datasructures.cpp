#include "datasructures.h"

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
