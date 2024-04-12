#ifndef CLIENTSETTING_H
#define CLIENTSETTING_H

#include <QSize>
#include <mutex>
#include <QRegularExpression>

#include <lazybox/toy/Instance.hpp>

#include "config.h"

#ifdef QT_DEBUG
#include "../../backend/backend.h"
#include "../../data_structure/datasructures.h"
#endif

class ClientSetting : public lbox::Instance<ClientSetting>
{
    friend class  lbox::Instance<ClientSetting>;

public:

    // ui setting
    const QSize MainWindowSize = {300, 800};
    const QSize MainWindowMinimumSize = {390, 720};
    const QSize LoginWindowSize = {300, 200};
    const QSize ChatWindowSize = {800, 600};
    const QSize ChatWindowMinimumSize = {600, 450};

    // room
    const QRegularExpression UserUidRegStr      {"^\\d{5}$"};
                                                // uid_uid
    const QRegularExpression ChatUidRegStr      {"^\\d{5}_\\d{5}$"};
    const QRegularExpression RoomUidRegStr      {"^\\d{8}$"};
                                                // roomid_from_to_date
    const QRegularExpression ChatEntryUidRegStr {"^\\d{8}_\\d{5}_\\d{5}_\\d+$"};


    // config
    Config config;

private:
    ClientSetting();

public:

#ifdef QT_DEBUG
    static QString DEBUG_login_password() { return "asd"; }
    static std::shared_ptr<UIUser> DEBUG_GetDebugUser() {
        static std::shared_ptr<UIUser> demo_user = std::make_shared<UIUser>();
        static std::once_flag demo_user_flag;
        std::call_once(demo_user_flag, [=](){
            demo_user->SetUid("10000");
            demo_user->SetName("asd");
            demo_user->SetSignature("sigsig_gnature");
            demo_user->SetProfilePixtureUrl("H:/Resources/paimeng.jpg");

            Backend::GetInstance()->AddUser(demo_user);
            Backend::GetInstance()->SetSelf(demo_user);

            std::shared_ptr<UIUser> user2 = std::make_shared<UIUser>();
            user2->SetUid("10001");
            user2->SetName("asd2");
            user2->SetSignature("sigsig_signature2");
            user2->SetProfilePixtureUrl("H:/Resources/paimeng.jpg");

            Backend::GetInstance()->AddUser(user2);

            int num = 1000'0000;

            auto group1 = std::make_shared<ChatGroup>();
            group1->SetUid(QString::number(num++));
            group1->SetName("1");
            group1->SetSignature("aaaa");
            group1->SetProfilePixtureUrl("H:/Resources/a.png");
            Backend::GetInstance()->AddChatGroup(group1);

            auto group2 = std::make_shared<ChatGroup>();
            group2->SetUid(QString::number(num++));
            group2->SetName("2");
            group2->SetSignature("bbb");
            group2->SetProfilePixtureUrl("H:/Resources/m2.png");
            Backend::GetInstance()->AddChatGroup(group2);

            auto group3 = std::make_shared<ChatGroup>();
            group3->SetUid(QString::number(num++));
            group3->SetName("3");
            group3->SetSignature("cc");
            group3->SetProfilePixtureUrl("H:/Resources/stand.png");
            Backend::GetInstance()->AddChatGroup(group3);

            auto group4 = std::make_shared<ChatGroup>();
            group4->SetUid(QString::number(num++));
            group4->SetName("4");
            group4->SetSignature("d");
            group4->SetProfilePixtureUrl("H:/Resources/stuff.jpg");
            Backend::GetInstance()->AddChatGroup(group4);
        });
        return demo_user;
    }
#endif

};

#define SETTING ClientSetting::GetInstance()

#endif // CLIENTSETTING_H
