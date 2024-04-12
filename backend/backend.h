#ifndef BACKEND_H
#define BACKEND_H

#include "../data_structure/datasructures.h"

class Backend
{
public:
    static Backend* GetInstance();
    static void Destroy();

    ~Backend() = default;

private:
    Backend();
    static Backend* instance_;

public:
#ifdef QT_DEBUG
    void SetSelf(std::shared_ptr<UIUser> self) { self_ = self; }
#endif
    std::shared_ptr<UIUser> SelfUser() { return self_; }

    std::shared_ptr<UIUser> GetUserFromUid(QString uid);
    std::shared_ptr<ChatGroup> GetGroupFromUid(QString uid);

    void AddUser(std::shared_ptr<UIUser> user);
    void AddChatGroup(std::shared_ptr<ChatGroup> group);

private:
    std::shared_ptr<UIUser> self_;

    std::unordered_map<QString, std::shared_ptr<UIUser>> uid_2_users_;
    std::unordered_map<QString, std::shared_ptr<ChatGroup>> uid_2_group_;
};

#endif // BACKEND_H
