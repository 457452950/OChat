#ifndef CLIENTSETTING_H
#define CLIENTSETTING_H

#include <QSize>
#include <mutex>

#include "../backend/backend.h"
#include "../data_structure/datasructures.h"

class ClientSetting
{
public:
    static ClientSetting* Init();
    static void Clear();
    static ClientSetting* GetInstance();

#ifdef QT_DEBUG
    static QString DEBUG_login_password() { return "asd"; }
    static std::shared_ptr<User> DEBUG_GetDebugUser() {
        static std::shared_ptr<User> demo_user = std::make_shared<User>();
        static std::once_flag demo_user_flag;
        std::call_once(demo_user_flag, [=](){
            demo_user->SetUid("10000");
            demo_user->SetUserName("asd");
            demo_user->SetSignature("sigsig_signature");
            demo_user->SetProfilePixtureUrl("H:/Resources/paimeng.jpg");

            Backend::GetInstance()->AddUser(demo_user);

            std::shared_ptr<User> user2 = std::make_shared<User>();
            user2->SetUid("10001");
            user2->SetUserName("asd2");
            user2->SetSignature("sigsig_signature2");
            user2->SetProfilePixtureUrl("H:/Resources/paimeng.jpg");

            Backend::GetInstance()->AddUser(user2);

            int num = 1000'0000;

            auto group1 = std::make_shared<ChatGroup>();
            group1->SetUid(QString::number(num++));
            group1->SetGroupName("1");
            group1->SetSignature("aaaa");
            group1->SetProfilePixtureUrl("H:/Resources/a.png");
            Backend::GetInstance()->AddChatGroup(group1);

            auto group2 = std::make_shared<ChatGroup>();
            group2->SetUid(QString::number(num++));
            group2->SetGroupName("2");
            group2->SetSignature("bbb");
            group2->SetProfilePixtureUrl("H:/Resources/m2.png");
            Backend::GetInstance()->AddChatGroup(group2);

            auto group3 = std::make_shared<ChatGroup>();
            group3->SetUid(QString::number(num++));
            group3->SetGroupName("3");
            group3->SetSignature("cc");
            group3->SetProfilePixtureUrl("H:/Resources/stand.png");
            Backend::GetInstance()->AddChatGroup(group3);

            auto group4 = std::make_shared<ChatGroup>();
            group4->SetUid(QString::number(num++));
            group4->SetGroupName("4");
            group4->SetSignature("d");
            group4->SetProfilePixtureUrl("H:/Resources/stuff.jpg");
            Backend::GetInstance()->AddChatGroup(group4);
        });
        return demo_user;
    }
#endif

private:
    static ClientSetting* instance_;
    ClientSetting();

public:
    QSize GetMainWindowSize();
    QSize GetLoginWindowSize();
    QSize GetChatWindowDefaultSize();

};

#endif // CLIENTSETTING_H
