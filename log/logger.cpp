#include "logger.h"

#include <QtLogging>

#include "../config/clientsetting.h"

void LoggerInit()
{
    qSetMessagePattern(SETTING->config.log_formater());
}
