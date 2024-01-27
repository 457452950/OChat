#include <QApplication>
#include <QtLogging>

#include <asio.hpp>
#include <asio/version.hpp>
#include <asio/ssl.hpp>

#include "log/logger.h"
#include "config/clientsetting.h"
#include "cache/datacache.h"
#include "windowmanager.h"

int main(int argc, char *argv[])
{
    LoggerInit();
    ClientSetting::Init();
    DataCache::Init();

    QApplication a(argc, argv);
    WindowManager::Init();

#ifdef QT_DEBUG
    qDebug() << "\n-------------------------------------\n"
             << "   DEBUG MODEL\n"
             << " test user name :" << ClientSetting::DEBUG_GetDebugUser()->UserName() << "\n"
             << " test password :" << ClientSetting::DEBUG_login_password() << "\n"
             << "-------------------------------------"
        ;
#endif

    auto res = a.exec();

    WindowManager::Close();
    ClientSetting::Clear();
    DataCache::Clear();

    return res;
}
