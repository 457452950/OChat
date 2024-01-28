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
    std::shared_ptr<User> GetUserFromUid(QString uid);
    std::shared_ptr<ChatGroup> GetGroupFromUid(QString uid);

    void AddUser(std::shared_ptr<User> user);
    void AddChatGroup(std::shared_ptr<ChatGroup> group);

private:
    std::unordered_map<QString, std::shared_ptr<User>> uid_2_users_;
    std::unordered_map<QString, std::shared_ptr<ChatGroup>> uid_2_group_;
};

#endif // BACKEND_H
