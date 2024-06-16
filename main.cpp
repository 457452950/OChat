#include <QApplication>
#include <QtLogging>

#include <asio.hpp>
#include <asio/version.hpp>
#include <asio/ssl.hpp>

#include "common/log/logger.h"
#include "common/config/client_setting.h"
#include "cache/data_cache.h"
#include "window_manager.h"

#ifdef QT_DEBUG
#include "common/debug.h"
#endif

int main(int argc, char *argv[]) {
    ClientSetting::GetInstance();
    LoggerInit();
    DataCache::GetInstance();

    QApplication a(argc, argv);
    WindowManager::GetInstance();

#ifdef QT_DEBUG
    debug::Init();
    qDebug() << "\n-------------------------------------\n"
             << "   DEBUG MODEL\n"
             << " test user name :" << debug::LocalMasterUser().name << "\n"
             << " test password :" << debug::MasterUserPasswd() << "\n"
             << "-------------------------------------";
#endif

    auto res = a.exec();

    WindowManager::Destroy();
    ClientSetting::Destroy();
    DataCache::Destroy();

    return res;
}
