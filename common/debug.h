#ifndef OCHAT__COMMON__DEBUG_H
#define OCHAT__COMMON__DEBUG_H

#include <mutex>

#include <QDebug>

#include "backend/backend.h"

#ifdef QT_DEBUG

namespace debug {

inline User MasterUser() {
    static auto user = User("10000", "asd");
    user.SetSignature("sigsig_signature1");
    user.SetProfilePixtureUrl("H:/Resources/image/paimeng.png");
    return user;
}
inline QString MasterUserPasswd() { return "asd"; }

inline void Init() {
    static std::once_flag demo_user_flag;

    std::call_once(demo_user_flag, [=]() {
        Backend::GetInstance()->AddUser(MasterUser());
        Backend::GetInstance()->SetSelf(MasterUser());

        User user2;
        user2.SetUid("10001");
        user2.SetName("asd2");
        user2.SetSignature("sigsig_signature2");
        user2.SetProfilePixtureUrl("H:/Resources/image/snake.jpg");

        Backend::GetInstance()->AddUser(user2);

        int num = 1000'0000;

        ChatRoom group1;
        group1.SetUid(QString::number(num++));
        group1.SetName("1");
        group1.SetSignature("aaaa");
        group1.SetProfilePixtureUrl("H:/Resources/a.png");
        Backend::GetInstance()->AddChatRoom(group1);

        ChatRoom group2;
        group2.SetUid(QString::number(num++));
        group2.SetName("2");
        group2.SetSignature("bbb");
        group2.SetProfilePixtureUrl("H:/Resources/m2.png");
        Backend::GetInstance()->AddChatRoom(group2);

        ChatRoom group3;
        group3.SetUid(QString::number(num++));
        group3.SetName("3");
        group3.SetSignature("cc");
        group3.SetProfilePixtureUrl("H:/Resources/stand.png");
        Backend::GetInstance()->AddChatRoom(group3);

        ChatRoom group4;
        group4.SetUid(QString::number(num++));
        group4.SetName("4");
        group4.SetSignature("d");
        group4.SetProfilePixtureUrl("H:/Resources/stuff.jpg");
        Backend::GetInstance()->AddChatRoom(group4);
    });
}

} // namespace debug


#endif

#endif // OCHAT__COMMON__DEBUG_H
