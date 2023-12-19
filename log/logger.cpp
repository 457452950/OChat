#include "logger.h"

#include <QtLogging>
#include <QString>

void LoggerInit()
{
    qSetMessagePattern(QString(LOG_MESSAGE_PATTERN));
}
