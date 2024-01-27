#ifndef CLIENTSETTING_H
#define CLIENTSETTING_H

#include <QSize>
#include <mutex>

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
            demo_user->SetUserName("asd");
            demo_user->SetSignature("sigsig_signature");
            demo_user->SetProfilePixtureUrl("H:/Resources/paimeng.jpg");
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
