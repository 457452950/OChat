#include <QApplication>
#include <QtLogging>

#include <asio.hpp>
#include <asio/version.hpp>
#include <asio/ssl.hpp>

#include "log/logger.h"
#include "windowmanager.h"

int main(int argc, char *argv[])
{
    LoggerInit();

    QApplication a(argc, argv);
    WindowManager::Init();

    qDebug() << "hello world.";

    auto res = a.exec();

    WindowManager::Close();

    return res;
}
