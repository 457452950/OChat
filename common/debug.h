#ifndef OCHAT__COMMON__DEBUG_H
#define OCHAT__COMMON__DEBUG_H

#include <mutex>

#include <QDebug>

#include "backend/backend.h"

#ifdef QT_DEBUG

namespace debug {

inline MasterUser LocalMasterUser() {
    static MasterUser user{"10000", "asd"};
    user.signature           = "sigsig_signature1";
    user.profile_pixture_url = "H:/Resources/image/paimeng.png";
    return user;
}
inline QString MasterUserPasswd() { return "asd"; }

inline void Init() {
    static std::once_flag demo_user_flag;

    std::call_once(demo_user_flag, [=]() {
        Backend::GetInstance()->AddUser(MasterUser());
        Backend::GetInstance()->SetSelf(MasterUser());

        User user2;
        user2.uid                 = "10001";
        user2.name                = "asd2";
        user2.signature           = "sigsig_signature2";
        user2.profile_pixture_url = "H:/Resources/image/snake.jpg";

        Backend::GetInstance()->AddUser(user2);

        int num = 1000'0000;

        ChatRoom group1;
        group1.uid                 = QString::number(num++);
        group1.name                = "1";
        group1.signature           = "aaaa";
        group1.profile_pixture_url = "H:/Resources/a.png";
        Backend::GetInstance()->AddChatRoom(group1);

        ChatRoom group2;
        group2.uid                 = QString::number(num++);
        group2.name                = "2";
        group2.signature           = "bbb";
        group2.profile_pixture_url = "H:/Resources/m2.png";
        Backend::GetInstance()->AddChatRoom(group2);

        ChatRoom group3;
        group3.uid                 = QString::number(num++);
        group3.name                = "3";
        group3.signature           = "cc";
        group3.profile_pixture_url = "H:/Resources/stand.png";
        Backend::GetInstance()->AddChatRoom(group3);

        ChatRoom group4;
        group4.uid                 = QString::number(num++);
        group4.name                = "4";
        group4.signature           = "d";
        group4.profile_pixture_url = "H:/Resources/stuff.jpg";
        Backend::GetInstance()->AddChatRoom(group4);
    });
}

} // namespace debug


#endif

#endif // OCHAT__COMMON__DEBUG_H
