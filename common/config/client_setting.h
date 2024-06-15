#ifndef OCHAT__COMMON_CONFIG__CLIENT_SETTING_H
#define OCHAT__COMMON_CONFIG__CLIENT_SETTING_H

#include <QSize>
#include <QRegularExpression>

#include <lazybox/toy/Instance.hpp>

#include "config.h"

#ifdef QT_DEBUG
// #include "backend/backend.h"
// #include "data_structure/data_sructures.h"
#endif

class ClientSetting : public lbox::Instance<ClientSetting> {
    friend class lbox::Instance<ClientSetting>;

    ClientSetting() = default;

public:
    // ui setting
    const QSize MainWindowSize        = {300, 800};
    const QSize MainWindowMinimumSize = {390, 720};
    const QSize LoginWindowSize       = {300, 200};
    const QSize ChatWindowSize        = {800, 600};
    const QSize ChatWindowMinimumSize = {600, 450};

    // ui default img
    const QString UserNoneImage{":/image/resource/image/awesomeface.png"};

    // room regix string
    const QRegularExpression UserUidRegStr{"^\\d{5}$"};
    // uid_uid
    const QRegularExpression ChatUidRegStr{"^\\d{5}_\\d{5}$"};
    const QRegularExpression RoomUidRegStr{"^\\d{8}$"};
    // roomid_from_to_date
    const QRegularExpression ChatEntryUidRegStr{"^\\d{8}_\\d{5}_\\d{5}_\\d+$"};


    // config
    Config config;

public:
};

#define SETTING ClientSetting::GetInstance()

#endif // OCHAT__COMMON_CONFIG__CLIENT_SETTING_H
